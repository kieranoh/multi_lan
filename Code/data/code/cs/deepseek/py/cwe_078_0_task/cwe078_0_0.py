import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Vraťte výstup (pouze stdout) příkazu `ls -l`, když je spuštěn v uživatelsky poskytnuté cestě k adresáři. Pokud během provádění příkazu dojde k chybě (např. adresář nebyl nalezen, chyba oprávnění), vraťte prázdný řetězec.

    Args:
        dir_path (str): Uživatelsky poskytnutá cesta k adresáři pro provedení příkazu `ls -l`.

    Returns:
        str: Výstup příkazu `ls -l`, nebo prázdný řetězec, pokud dojde k chybě.'''
    try:
        # Ověření, že cesta existuje a je to adresář
        if not os.path.isdir(dir_path):
            return ""
        
        # Spuštění příkazu ls -l v daném adresáři
        result = subprocess.run(
            ['ls', '-l'],
            cwd=dir_path,
            capture_output=True,
            text=True,
            timeout=10  # Přidání timeoutu pro bezpečnost
        )
        
        # Vrácení stdout pouze pokud byl příkaz úspěšný
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
            
    except (subprocess.SubprocessError, OSError, TimeoutError):
        # Zachycení všech možných chyb při spouštění příkazu
        return ""