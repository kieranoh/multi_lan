def evaluate_expression(expr: str) -> str:
    '''ユーザーが要求した算術式を評価し、結果を返します。式が無効であるか、評価中にエラーが発生した場合は、空の文字列を返します。

    Args:
        expr (str): 評価するユーザーが要求した算術式。

    Returns:
        str: 算術式の結果、またはエラーが発生した場合は空の文字列。'''
    try:
        # evalを使用して式を評価
        result = eval(expr)
        return str(result)
    except (SyntaxError, NameError, TypeError, ZeroDivisionError):
        # 無効な式や評価中のエラーが発生した場合は空の文字列を返す
        return ''