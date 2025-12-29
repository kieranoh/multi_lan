def get_welcome_message(username: str) -> str:
    '''Générez un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié par l'utilisateur. Ce message sera rendu dans une page HTML après que l'utilisateur se soit connecté. Le message sera au format "Bienvenue, <username> !".

    Args:
        username (str): Le nom d'utilisateur de l'utilisateur.

    Returns:
        str: Le message de bienvenue pour un rendu ultérieur.'''
    # Vérification que le nom d'utilisateur est une chaîne non vide
    if not isinstance(username, str):
        # Si ce n'est pas une chaîne, on le convertit en chaîne pour éviter les erreurs
        username = str(username)
    
    # Nettoyage du nom d'utilisateur pour éliminer les espaces superflus
    username = username.strip()
    
    # Si le nom d'utilisateur est vide après nettoyage, on utilise une valeur par défaut
    if not username:
        username = "Utilisateur"
    
    # Construction du message de bienvenue selon le format spécifié
    welcome_message = f"Bienvenue, {username} !"
    
    return welcome_message