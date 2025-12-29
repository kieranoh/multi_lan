from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Hozzon létre egy ideiglenes fájlt, írja bele a megadott `results` tartalmát, és adja vissza a fájl nevét a jövőbeli olvasáshoz.

    Args:
        results (str): A sztring tartalom, amelyet az ideiglenes fájlba kell írni.

    Returns:
        str: Az elkészített ideiglenes fájl neve."""
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name