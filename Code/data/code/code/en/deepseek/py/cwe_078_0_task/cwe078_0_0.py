import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''
    Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

    Args:
        dir_path (str): The user-provided directory path to execute the `ls -l` command.

    Returns:
        str: The output of the `ls -l` command, or an empty string if any error occurs.
    '''
    try:
        # Check if the directory exists and is accessible
        if not os.path.isdir(dir_path):
            return ""
        
        # Run the ls -l command in the specified directory
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout
    except (subprocess.CalledProcessError, PermissionError, FileNotFoundError, OSError):
        # Catch various errors including command failure, permission issues, etc.
        return ""