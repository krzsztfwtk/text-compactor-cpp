from pathlib import Path # C++ filesystem equivalent

class FileManager:
    def write_to_file(self, file_path: str, content: str):
        path = Path(file_path)
        # Ensure the directory exists
        path.parent.mkdir(parents=True, exist_ok=True)
        
        with path.open('w', encoding='utf-8') as f:
            f.write(content)

    def read_from_file(self, file_path: str) -> str:
        path = Path(file_path)
        with path.open('r', encoding='utf-8') as f:
            return f.read()
