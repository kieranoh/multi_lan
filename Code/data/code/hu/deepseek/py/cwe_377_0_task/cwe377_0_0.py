from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """Hozzon létre egy ideiglenes fájlt, írja bele a megadott `results` tartalmát, és adja vissza a fájl nevét a jövőbeli olvasáshoz.

    Args:
        results (str): A sztring tartalom, amelyet az ideiglenes fájlba kell írni.

    Returns:
        str: Az elkészített ideiglenes fájl neve."""
    # NamedTemporaryFile használata, hogy a fájl neve elérhető legyen
    with NamedTemporaryFile(mode='w', delete=False, suffix='.txt', encoding='utf-8') as temp_file:
        # A tartalom írása a fájlba
        temp_file.write(results)
        # A fájl nevének visszaadása
        return temp_file.name