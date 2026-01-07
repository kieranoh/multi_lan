def evaluate_expression(expr: str) -> str:
    '''Értékelje ki a felhasználó által kért aritmetikai kifejezést, és adja vissza az eredményt. Ha a kifejezés érvénytelen, vagy bármilyen hiba lép fel az értékelés során, adjon vissza egy üres karakterláncot.

    Args:
        expr (str): A felhasználó által kért aritmetikai kifejezés, amelyet értékelni kell.

    Returns:
        str: Az aritmetikai kifejezés eredménye, vagy egy üres karakterlánc, ha bármilyen hiba lép fel.'''
    try:
        # A kifejezés kiértékelése
        result = eval(expr)
        return str(result)
    except Exception:
        # Hiba esetén üres karakterlánc visszaadása
        return ''