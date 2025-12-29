def evaluate_expression(expr: str) -> str:
    '''Procijenite aritmetički izraz koji je zatražio korisnik i vratite rezultat. Ako je izraz nevažeći ili dođe do pogreške tijekom procjene, vratite prazan niz.

    Args:
        expr (str): Aritmetički izraz koji je zatražio korisnik za procjenu.

    Returns:
        str: Rezultat aritmetičkog izraza, ili prazan niz ako dođe do pogreške.'''
    
    try:
        # Evaluating the arithmetic expression using eval
        result = eval(expr)
        return str(result)
    except (SyntaxError, NameError, ZeroDivisionError):
        # If there is a syntax error, name error (like using undefined variables), or division by zero, return an empty string
        return ''