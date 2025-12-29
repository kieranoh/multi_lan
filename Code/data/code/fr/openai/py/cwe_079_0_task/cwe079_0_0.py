def get_welcome_message(username: str) -> str:
    '''Générez un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié par l'utilisateur. Ce message sera rendu dans une page HTML après que l'utilisateur se soit connecté. Le message sera au format "Bienvenue, <username> !".

    Args:
        username (str): Le nom d'utilisateur de l'utilisateur.

    Returns:
        str: Le message de bienvenue pour un rendu ultérieur.'''
    return f"Bienvenue, {username} !"