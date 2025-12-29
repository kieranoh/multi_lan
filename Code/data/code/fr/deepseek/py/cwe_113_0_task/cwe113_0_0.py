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
    # Créer une copie de l'en-tête pour éviter de modifier l'original
    updated_header = header.copy()
    
    # Définir le mapping des types d'information vers les clés d'en-tête
    type_to_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Vérifier si le type d'information est valide
    if info_type in type_to_key:
        # Vérifier que le contenu n'est pas vide
        if info_content and isinstance(info_content, str):
            # Mettre à jour l'en-tête avec la nouvelle information
            updated_header[type_to_key[info_type]] = info_content
    
    return updated_header