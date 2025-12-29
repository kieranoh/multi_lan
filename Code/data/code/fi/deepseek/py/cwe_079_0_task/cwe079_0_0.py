def get_welcome_message(username: str) -> str:
    '''Luo tervetuloviesti käyttäjälle käyttäjän määrittämällä käyttäjänimellä. Tämä viesti näytetään HTML-sivulla käyttäjän kirjauduttua sisään. Viestin muoto on "Tervetuloa, <käyttäjänimi>!".

    Args:
        username (str): Käyttäjän käyttäjänimi.

    Returns:
        str: Tervetuloviesti jatkokäsittelyä varten.'''
    return f"Tervetuloa, {username}!"