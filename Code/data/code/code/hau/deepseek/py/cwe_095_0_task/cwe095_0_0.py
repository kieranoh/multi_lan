def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    try:
        # 빈 문자열이나 None 체크
        if not expr or expr.strip() == "":
            return ""
        
        # 안전한 문자만 허용: 숫자, 기본 연산자, 괄호, 공백, 소수점
        allowed_chars = set('0123456789+-*/(). ')
        if not all(c in allowed_chars for c in expr):
            return ""
        
        # 잠재적인 위험한 표현식 필터링
        dangerous_patterns = ['__', 'import', 'eval', 'exec', 'open', 'os', 'sys']
        for pattern in dangerous_patterns:
            if pattern in expr.lower():
                return ""
        
        # 표현식 평가
        result = eval(expr, {"__builtins__": {}}, {})
        
        # 결과를 문자열로 변환
        if isinstance(result, (int, float)):
            # 정수인 경우 소수점 없이, 실수인 경우 적절히 표시
            if isinstance(result, int):
                return str(result)
            else:
                # 부동소수점 오차 처리
                return str(round(result, 10)).rstrip('0').rstrip('.')
        else:
            return ""
            
    except (SyntaxError, NameError, TypeError, ZeroDivisionError, 
            MemoryError, ValueError, ArithmeticError, Exception):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""