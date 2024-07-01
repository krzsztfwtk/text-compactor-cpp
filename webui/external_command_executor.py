import subprocess

class ExternalCommandExecutor:
    def __init__(self, exe_path):
        self.exe_path = exe_path

    def construct_command(self, input_file_path, output_file_path, config_file_path, query_file_path=None):
        command = [self.exe_path, '-i', str(input_file_path), '-o', str(output_file_path), '-c', str(config_file_path)]
        if query_file_path:
            command.extend(['-q', str(query_file_path)])
        return command

    def execute_command(self, command):
        try:
            process = subprocess.run(command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            return process.stdout, process.stderr
        except subprocess.CalledProcessError as e:
            return '', e.stderr
