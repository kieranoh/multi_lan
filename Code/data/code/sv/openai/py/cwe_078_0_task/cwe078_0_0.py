import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Returnera utdata (endast stdout) från `ls -l` kommandot när det körs i en användarangiven katalogsökväg. Om något fel uppstår under kommandots körning (t.ex. katalogen hittades inte, behörighetsfel), returnera en tom sträng.

    Args:
        dir_path (str): Den användarangivna katalogsökvägen för att köra `ls -l` kommandot.

    Returns:
        str: Utdatan från `ls -l` kommandot, eller en tom sträng om något fel uppstår.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''