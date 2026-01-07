import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Kreirajte privremenu datoteku, upišite pružene `rezultate` u nju i vratite ime datoteke za buduće čitanje.

    Args:
        results (str): Sadržaj stringa koji treba upisati u privremenu datoteku.

    Returns:
        str: Ime privremene datoteke koja je kreirana.
    """
    # Kreiraj privremenu datoteku koja se neće automatski obrisati
    # Koristimo 'delete=False' da bi datoteka ostala dostupna za čitanje
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Zapiši sadržaj u datoteku
        temp_file.write(results)
        # Vrati ime datoteke
        return temp_file.name