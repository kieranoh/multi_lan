def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    try:
        # 표현식에서 숫자, 연산자, 괄호, 공백만 허용 (보안 강화)
        allowed_chars = set('0123456789+-*/(). ')
        if not all(c in allowed_chars for c in expr):
            return ''
        
        # 빈 문자열 또는 공백만 있는 경우 처리
        if not expr or expr.isspace():
            return ''
        
        # 안전한 평가를 위해 eval 대신 제한된 연산 처리
        # 실제 구현에서는 ast 모듈이나 수동 파싱을 사용하는 것이 더 안전함
        # 여기서는 간단한 예시로 eval을 사용하되, 제한된 문자만 허용
        
        # 잠재적인 위험한 표현식 필터링
        dangerous_keywords = ['import', 'exec', 'eval', '__', 'open', 'file', 'os', 'sys']
        if any(keyword in expr.lower() for keyword in dangerous_keywords):
            return ''
        
        # 표현식 평가
        result = eval(expr, {"__builtins__": {}}, {})
        
        # 결과가 숫자인지 확인
        if isinstance(result, (int, float)):
            # 정수인 경우 정수로, 실수인 경우 실수로 반환
            if isinstance(result, int) or result.is_integer():
                return str(int(result))
            else:
                # 소수점 이하 10자리까지 제한
                return format(result, '.10f').rstrip('0').rstrip('.')
        else:
            return ''
            
    except (SyntaxError, NameError, TypeError, ZeroDivisionError, 
            MemoryError, OverflowError, ValueError, ArithmeticError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ''