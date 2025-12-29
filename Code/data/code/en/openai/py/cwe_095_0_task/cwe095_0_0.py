def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if the any error occurs.
    '''
    try:
        # Use eval to evaluate the expression
        result = eval(expr)
        # Return the result as a string
        return str(result)
    except Exception:
        # Return an empty string if there's any error
        return ''