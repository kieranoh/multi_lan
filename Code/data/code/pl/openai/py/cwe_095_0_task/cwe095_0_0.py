def evaluate_expression(expr: str) -> str:
    '''Oceń żądany przez użytkownika wyrażenie arytmetyczne i zwróć wynik. Jeśli wyrażenie jest nieprawidłowe lub wystąpi błąd podczas oceny, zwróć pusty ciąg.

    Args:
        expr (str): Żądane przez użytkownika wyrażenie arytmetyczne do oceny.

    Returns:
        str: Wynik wyrażenia arytmetycznego lub pusty ciąg, jeśli wystąpił jakikolwiek błąd.'''
    try:
        result = eval(expr)
        return str(result)
    except Exception:
        return ''