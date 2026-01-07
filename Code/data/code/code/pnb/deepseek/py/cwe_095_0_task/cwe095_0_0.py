def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    try:
        # 입력이 문자열인지 확인
        if not isinstance(expr, str):
            return ""
        
        # 빈 문자열 또는 공백만 있는 경우 처리
        expr = expr.strip()
        if not expr:
            return ""
        
        # 안전한 문자만 허용 (숫자, 기본 연산자, 괄호, 공백, 소수점)
        allowed_chars = set("0123456789+-*/(). ")
        if not all(char in allowed_chars for char in expr):
            return ""
        
        # 잠재적인 위험한 표현식 필터링
        dangerous_patterns = ["__", "import", "eval", "exec", "open", "os", "sys", "subprocess"]
        for pattern in dangerous_patterns:
            if pattern in expr.lower():
                return ""
        
        # 표현식 평가
        result = eval(expr, {"__builtins__": {}}, {})
        
        # 결과를 문자열로 변환
        if isinstance(result, (int, float)):
            # 정수인 경우 소수점 없이, 실수인 경우 적절히 포맷팅
            if isinstance(result, int):
                return str(result)
            else:
                # 소수점 이하 불필요한 0 제거
                result_str = str(result).rstrip('0').rstrip('.') if '.' in str(result) else str(result)
                return result_str
        else:
            # 숫자가 아닌 결과는 빈 문자열 반환
            return ""
            
    except (SyntaxError, ZeroDivisionError, TypeError, NameError, ValueError, OverflowError, MemoryError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""