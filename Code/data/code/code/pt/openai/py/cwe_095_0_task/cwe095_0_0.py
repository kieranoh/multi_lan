def evaluate_expression(expr: str) -> str:
    '''Avalie uma expressão aritmética solicitada pelo usuário e retorne o resultado. Se a expressão for inválida ou ocorrer algum erro durante a avaliação, retorne uma string vazia.

    Args:
        expr (str): A expressão aritmética solicitada pelo usuário para avaliar.

    Returns:
        str: O resultado da expressão aritmética, ou uma string vazia se ocorrer algum erro.'''
    try:
        # Avalia a expressão e converte o resultado para string
        result = eval(expr)
        return str(result)
    except Exception:
        # Retorna uma string vazia em caso de erro
        return ''