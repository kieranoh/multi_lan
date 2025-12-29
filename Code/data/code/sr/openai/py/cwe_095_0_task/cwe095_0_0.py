def evaluate_expression(expr: str) -> str:
    '''Evaluirajte aritmetički izraz koji je korisnik zatražio i vratite rezultat. Ako je izraz nevažeći ili dođe do greške tokom evaluacije, vratite prazan string.

    Args:
        expr (str): Aritmetički izraz koji je korisnik zatražio za evaluaciju.

    Returns:
        str: Rezultat aritmetičkog izraza, ili prazan string ako dođe do greške.'''
    try:
        # Evaluiramo izraz koristeći eval funkciju.
        result = eval(expr)
        # Vraćamo rezultat kao string.
        return str(result)
    except (SyntaxError, NameError, ZeroDivisionError):
        # U slučaju greške, vraćamo prazan string.
        return ''