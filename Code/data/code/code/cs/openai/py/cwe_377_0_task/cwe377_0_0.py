from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Vytvořte dočasný soubor, zapište do něj poskytnuté `results` a vraťte název souboru pro budoucí čtení.

    Args:
        results (str): Řetězcový obsah, který se má zapsat do dočasného souboru.

    Returns:
        str: Název dočasného souboru, který byl vytvořen."""
    
    with NamedTemporaryFile(delete=False, mode='w', encoding='utf-8') as temp_file:
        temp_file.write(results)
        return temp_file.name