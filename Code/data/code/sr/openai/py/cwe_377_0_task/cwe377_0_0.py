from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Kreirajte privremenu datoteku, upišite pružene `rezultate` u nju i vratite ime datoteke za buduće čitanje.

    Args:
        results (str): Sadržaj stringa koji treba upisati u privremenu datoteku.

    Returns:
        str: Ime privremene datoteke koja je kreirana."""
    
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name