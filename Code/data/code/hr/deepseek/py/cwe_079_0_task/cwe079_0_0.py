def get_welcome_message(username: str) -> str:
    '''Generirajte poruku dobrodošlice za korisnika s korisničkim imenom koje je korisnik odredio. Ova poruka će se prikazati na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <username>!".

    Args:
        username (str): Korisničko ime korisnika.

    Returns:
        str: Poruka dobrodošlice za daljnje prikazivanje.'''
    return f"Dobrodošli, {username}!"