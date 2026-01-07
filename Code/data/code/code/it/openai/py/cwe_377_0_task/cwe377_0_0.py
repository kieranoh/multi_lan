from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Crea un file temporaneo, scrivi i `results` forniti e restituisci il nome del file per letture future.

    Args:
        results (str): Il contenuto della stringa da scrivere nel file temporaneo.

    Returns:
        str: Il nome del file del file temporaneo creato."""
    
    with NamedTemporaryFile(delete=False, mode='w+') as temp_file:
        temp_file.write(results)
        return temp_file.name