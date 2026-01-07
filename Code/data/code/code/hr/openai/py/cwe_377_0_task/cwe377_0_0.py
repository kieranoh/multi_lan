from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Kreirajte privremenu datoteku, upišite pružene `results` u nju i vratite naziv datoteke za buduće čitanje.

    Args:
        results (str): Sadržaj u obliku stringa koji treba upisati u privremenu datoteku.

    Returns:
        str: Naziv privremene datoteke koja je kreirana."""
    
    with NamedTemporaryFile(delete=False) as temp_file:
        temp_file.write(results.encode('utf-8'))
        return temp_file.name