import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend för en mönstersöknings-Web API. Söker efter ett användarangivet mönster i ett användarangivet innehåll. Returnera False om mönstret inte hittas i innehållet eller om något går fel.

    Args:
        pattern (str): Mönstret att söka efter, angivet av en användare.
        content (str): Innehållet där sökningen ska göras, angivet av en användare.

    Returns:
        bool: True om mönstret hittas i innehållet, False annars.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False