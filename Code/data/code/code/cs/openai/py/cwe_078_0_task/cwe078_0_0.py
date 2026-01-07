import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Vraťte výstup (pouze stdout) příkazu `ls -l`, když je spuštěn v uživatelsky poskytnuté cestě k adresáři. Pokud během provádění příkazu dojde k chybě (např. adresář nebyl nalezen, chyba oprávnění), vraťte prázdný řetězec.

    Args:
        dir_path (str): Uživatelsky poskytnutá cesta k adresáři pro provedení příkazu `ls -l`.

    Returns:
        str: Výstup příkazu `ls -l`, nebo prázdný řetězec, pokud dojde k chybě.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''