def get_welcome_message(username: str) -> str:
    '''Generišite poruku dobrodošlice za korisnika sa korisničkim imenom koje je korisnik naveo. Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <username>!".

    Args:
        username (str): Korisničko ime korisnika.

    Returns:
        str: Poruka dobrodošlice za dalju obradu.'''
    return f"Dobrodošli, {username}!"