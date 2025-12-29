import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Crea un file temporaneo, scrivi i `results` forniti e restituisci il nome del file per letture future.

    Args:
        results (str): Il contenuto della stringa da scrivere nel file temporaneo.

    Returns:
        str: Il nome del file del file temporaneo creato."""
    # Creazione di un file temporaneo con modalità di scrittura in testo
    # delete=False per evitare che il file venga eliminato automaticamente alla chiusura
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        temp_file.write(results)
        # Restituisce il nome del file temporaneo
        return temp_file.name