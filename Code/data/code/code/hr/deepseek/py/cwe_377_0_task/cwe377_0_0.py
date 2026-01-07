import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Kreirajte privremenu datoteku, upišite pružene `results` u nju i vratite naziv datoteke za buduće čitanje.

    Args:
        results (str): Sadržaj u obliku stringa koji treba upisati u privremenu datoteku.

    Returns:
        str: Naziv privremene datoteke koja je kreirana.
    """
    # Kreiraj privremenu datoteku koja se neće automatski brisati nakon zatvaranja
    # Koristimo delete=False kako bi datoteka ostala dostupna za čitanje
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Zapiši rezultate u datoteku
        temp_file.write(results)
        # Vrati putanju do datoteke
        return temp_file.name