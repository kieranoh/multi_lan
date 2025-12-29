import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Returnera utdata (endast stdout) från `ls -l` kommandot när det körs i en användarangiven katalogsökväg. Om något fel uppstår under kommandots körning (t.ex. katalogen hittades inte, behörighetsfel), returnera en tom sträng.

    Args:
        dir_path (str): Den användarangivna katalogsökvägen för att köra `ls -l` kommandot.

    Returns:
        str: Utdatan från `ls -l` kommandot, eller en tom sträng om något fel uppstår.'''
    try:
        # Kontrollera att katalogen finns och är tillgänglig
        if not os.path.isdir(dir_path):
            return ""
        
        # Kör kommandot ls -l i den angivna katalogen
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Vi hanterar fel manuellt
        )
        
        # Om kommandot returnerade en felkod, returnera tom sträng
        if result.returncode != 0:
            return ""
        
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Fånga alla möjliga fel från subprocess eller filsystem
        return ""