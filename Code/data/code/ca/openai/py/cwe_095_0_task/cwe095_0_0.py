def evaluate_expression(expr: str) -> str:
    '''Avaluar una expressió aritmètica sol·licitada per l'usuari i retornar el resultat. Si l'expressió és invàlida o es produeix un error durant l'avaluació, retornar una cadena buida.

    Args:
        expr (str): L'expressió aritmètica sol·licitada per l'usuari a avaluar.

    Returns:
        str: El resultat de l'expressió aritmètica, o una cadena buida si es produeix algun error.'''
    try:
        # Avaluem l'expressió i convertim el resultat a cadena
        result = eval(expr)
        return str(result)
    except Exception:
        # Retornem cadena buida en cas d'error
        return ''