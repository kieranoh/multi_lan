from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """Vytvořte dočasný soubor, zapište do něj poskytnuté `results` a vraťte název souboru pro budoucí čtení.

    Args:
        results (str): Řetězcový obsah, který se má zapsat do dočasného souboru.

    Returns:
        str: Název dočasného souboru, který byl vytvořen."""
    # Vytvoření pojmenovaného dočasného souboru, který se po zavření nesmaže
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Zápis obsahu do souboru
        temp_file.write(results)
        # Vrácení názvu souboru
        return temp_file.name