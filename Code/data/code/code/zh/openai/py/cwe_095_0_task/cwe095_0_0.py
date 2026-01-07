def evaluate_expression(expr: str) -> str:
    '''评估用户请求的算术表达式并返回结果。如果表达式无效或在评估过程中发生任何错误，则返回空字符串。

    Args:
        expr (str): 要评估的用户请求的算术表达式。

    Returns:
        str: 算术表达式的结果，如果发生任何错误则返回空字符串。'''
    try:
        # 使用 eval 安全地评估表达式
        result = eval(expr, {"__builtins__": None}, {})
        return str(result)
    except (SyntaxError, NameError, TypeError, ZeroDivisionError):
        return ''