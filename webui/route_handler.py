from flask import request, jsonify, render_template, current_app
from webui.configuration import Configuration
from webui.file_manager import FileManager
from webui.external_command_executor import ExternalCommandExecutor
from pathlib import Path # C++ filesystem equivalent
import platform
import subprocess
import json
import uuid
import os

class RouteHandler:
    def __init__(self):
        self.file_manager = FileManager()
        self.config = Configuration()

        base_dir = Path(__file__).resolve().parent
        exe_name = "main.exe" if platform.system() == "Windows" else "main"
        self.exe_path = base_dir / '../cpp/bin' / exe_name

        # Check if executable exists, if not, compile it
        if not self.exe_path.exists():
            self.compile_cpp_project(base_dir)

    def compile_cpp_project(self, base_dir):
        cpp_dir = base_dir / '..' / 'cpp'
        compile_commands = ["mingw64-make", "mingw32-make"] if platform.system() == "Windows" else ["make"]

        for compile_command in compile_commands:
            try:
                subprocess.check_call(compile_command, cwd=cpp_dir, shell=True)
                print(f"Successfully compiled the C++ project using {compile_command}.")
                return
            except subprocess.CalledProcessError as e:
                print(f"Failed to compile the C++ project using {compile_command}: {e}")

        print("Failed to compile the C++ project with all available commands.")

    def home(self):
        return render_template('home.html')

    def text_compactor(self):
        return render_template('text_compactor.html')

    def insight_search(self):
        return render_template('insight_search.html')

    def compact_text(self):
        with current_app.app_context():
            data = request.json
            config_data = self.config.get_configuration(data)
            input_text = data['input']
            query_text = data.get('query', '')  # Get query text, default to empty string

            # Generate unique file names
            unique_id = uuid.uuid4().hex
            input_file_path = Path('resources') / f'input_{unique_id}.tmp'
            output_file_path = Path('resources') / f'result_{unique_id}.tmp'
            config_file_path = Path('cpp/config') / f'config_{unique_id}.json'
            query_file_path = Path('resources') / f'query_{unique_id}.tmp'

            # Write input and config data to files
            self.file_manager.write_to_file(input_file_path, input_text)
            self.file_manager.write_to_file(config_file_path, json.dumps(config_data, indent=4))
            if query_text:  # Write query file only if query text is provided
                self.file_manager.write_to_file(query_file_path, query_text)

            executor = ExternalCommandExecutor(self.exe_path)
            
            if query_text:
                command = executor.construct_command(input_file_path, output_file_path, config_file_path, query_file_path)
            else:
                command = executor.construct_command(input_file_path, output_file_path, config_file_path)

            print("before running cpp...", command)
            stdout, stderr = executor.execute_command(command)
            print("after running cpp...")

            if stderr:
                result = {'error': stderr}
            else:
                try:
                    result_content = self.file_manager.read_from_file(output_file_path)
                    result = {'output': result_content}
                except Exception as file_error:
                    result = {'error': f'Failed to read the result file: {str(file_error)}'}

            # Clean up temporary files

            try:
                if os.path.exists(input_file_path):
                    os.remove(input_file_path)
                if os.path.exists(output_file_path):
                    os.remove(output_file_path)
                if os.path.exists(config_file_path):
                    os.remove(config_file_path)
                if query_text and os.path.exists(query_file_path):
                    os.remove(query_file_path)
                if os.path.exists(config_file_path):
                    os.remove(config_file_path)
            except Exception as cleanup_error:
                print(f"Failed to clean up temporary files: {str(cleanup_error)}")

            return jsonify(result)