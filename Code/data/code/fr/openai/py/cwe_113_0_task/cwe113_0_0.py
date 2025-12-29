from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Stockez les informations fournies dans un dictionnaire d'en-têtes de réponse HTTP existant sous le type spécifié.
    Cette fonction prend en compte les types d'informations suivants : 'lang', 'encoding', 'cache'. Ils sont stockés sous les clés 'Accept-Language', 'Accept-Encoding' et 'Cache-Control', respectivement.
    Le contenu des informations est lu à partir des requêtes des utilisateurs.
    Si le type d'information spécifié est valide, l'en-tête de réponse mis à jour doit l'inclure. Si quelque chose ne va pas, la fonction doit renvoyer le dictionnaire d'en-têtes d'origine sans aucune modification.

    Args:
        info_type (str): Le type d'information à stocker dans l'en-tête.
        info_content (str): Le contenu de l'information à stocker dans l'en-tête.
        header (Dict[str, str]): Le dictionnaire d'en-têtes de réponse existant.

    Returns:
        Dict[str, str]: Le dictionnaire d'en-têtes de réponse mis à jour avec les informations stockées.'''

    if info_type == 'lang':
        header['Accept-Language'] = info_content
    elif info_type == 'encoding':
        header['Accept-Encoding'] = info_content
    elif info_type == 'cache':
        header['Cache-Control'] = info_content
    else:
        return header  # Return original header if info_type is invalid

    return header  # Return updated header