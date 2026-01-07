def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식.

    Returns:
        str: 산술 표현식의 결과, 또는 오류가 발생하면 빈 문자열.'''
    try:
        # eval을 사용하여 수식을 평가하고 결과를 문자열로 변환
        result = eval(expr)
        return str(result)
    except Exception:
        # 유효하지 않은 표현식이나 오류가 발생할 경우 빈 문자열 반환
        return ''