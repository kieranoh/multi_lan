import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Vérifiez si l'URL cible fournie est dans le domaine fourni.
Si c'est le cas, renvoyez l'URL cible pour la redirection ; sinon, revenez à l'URL du domaine pour la redirection.
Utilisez le protocole https.

Exemples:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): La chaîne d'URL cible.
    domain (str): La chaîne de domaine, sans protocole.

Returns:
    str: La chaîne d'URL pour la redirection.'''
    # Normaliser le domaine pour supprimer les points de début/fin
    domain = domain.strip().lower()
    
    # Analyser l'URL cible
    parsed_target = urlparse(target)
    
    # Extraire le nom d'hôte de l'URL cible
    target_hostname = parsed_target.hostname
    
    # Si l'URL cible n'a pas d'hôte valide, retourner le domaine avec https
    if not target_hostname:
        return f"https://{domain}"
    
    # Normaliser le nom d'hôte cible
    target_hostname = target_hostname.lower()
    
    # Vérifier si le domaine cible se termine par le domaine fourni
    # Utiliser une expression régulière pour s'assurer que c'est un sous-domaine valide
    # ou le domaine exact, et pas un domaine différent qui se termine par la même chaîne
    pattern = r'^(.*\.)?' + re.escape(domain) + '$'
    
    if re.match(pattern, target_hostname):
        # Si l'URL cible utilise déjà https, la retourner telle quelle
        if parsed_target.scheme == 'https':
            return target
        # Sinon, reconstruire l'URL avec https
        else:
            # Conserver le chemin, les paramètres de requête et le fragment
            return f"https://{target_hostname}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
    else:
        # Retourner le domaine avec https
        return f"https://{domain}"