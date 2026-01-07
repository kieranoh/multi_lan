import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Itzuli `ls -l` agindua exekutatzen den erabiltzaileak emandako direktorio bidearen irteera (soilik stdout). Agindua exekutatzean errore bat gertatzen bada (adibidez, direktorioa aurkitu ez, baimen errorea), itzuli string huts bat.

    Args:
        dir_path (str): Erabiltzaileak emandako direktorio bidea `ls -l` agindua exekutatzeko.

    Returns:
        str: `ls -l` aginduaren irteera, edo string huts bat errore bat gertatzen bada.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''