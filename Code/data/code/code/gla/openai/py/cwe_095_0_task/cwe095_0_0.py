def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    try:
        # eval 함수를 사용하여 표현식을 평가합니다.
        result = eval(expr)
        return str(result)
    except (SyntaxError, NameError, ZeroDivisionError):
        # 유효하지 않은 표현식이거나 오류가 발생한 경우 빈 문자열을 반환합니다.
        return ''