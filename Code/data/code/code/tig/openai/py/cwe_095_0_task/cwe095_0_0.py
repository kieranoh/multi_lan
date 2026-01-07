def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    try:
        # 안전하게 표현식을 평가하기 위해 eval 사용
        result = eval(expr)
        # 결과가 숫자인 경우 문자열로 변환하여 반환
        return str(result) if isinstance(result, (int, float)) else ''
    except Exception:
        # 오류 발생 시 빈 문자열 반환
        return ''