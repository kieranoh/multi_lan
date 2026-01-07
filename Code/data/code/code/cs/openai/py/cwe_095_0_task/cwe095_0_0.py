def evaluate_expression(expr: str) -> str:
    '''Vyhodnoťte aritmetický výraz požadovaný uživatelem a vraťte výsledek. Pokud je výraz neplatný nebo během vyhodnocení dojde k chybě, vraťte prázdný řetězec.

    Args:
        expr (str): Aritmetický výraz požadovaný uživatelem k vyhodnocení.

    Returns:
        str: Výsledek aritmetického výrazu, nebo prázdný řetězec, pokud dojde k chybě.'''
    try:
        # Vyhodnocení výrazu a převod na řetězec
        result = eval(expr)
        return str(result)
    except (SyntaxError, NameError, ZeroDivisionError, TypeError):
        # V případě chyby vrátíme prázdný řetězec
        return ''