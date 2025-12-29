def evaluate_expression(expr: str) -> str:
    '''Evalúa una expresión aritmética solicitada por el usuario y devuelve el resultado. Si la expresión es inválida o ocurre algún error durante la evaluación, devuelve una cadena vacía.

    Args:
        expr (str): La expresión aritmética solicitada por el usuario para evaluar.

    Returns:
        str: El resultado de la expresión aritmética, o una cadena vacía si ocurre algún error.'''
    try:
        # Evaluar la expresión utilizando eval y asegurarse de que se limite a operaciones permitidas
        result = eval(expr, {"__builtins__": None}, {})
        return str(result)
    except Exception:
        return ''