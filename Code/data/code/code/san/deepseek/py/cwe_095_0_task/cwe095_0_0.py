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
        
        # 안전한 평가를 위해 허용된 문자만 포함하는지 확인
        # 숫자, 연산자(+-*/), 공백, 괄호, 소수점만 허용
        allowed_chars = set('0123456789+-*/(). ')
        if not all(c in allowed_chars for c in expr):
            return ""
        
        # 잠재적인 보안 문제를 방지하기 위해 eval 대신 안전한 평가 방법 사용
        # 여기서는 간단한 구현을 위해 eval을 사용하지만 실제 환경에서는 더 안전한 방법을 고려해야 함
        # 실제 프로덕션 환경에서는 ast.literal_eval이나 수식 파싱 라이브러리를 사용하는 것이 좋음
        
        # 0으로 나누기 방지
        if '/0' in expr or '/ 0' in expr:
            return ""
        
        # 표현식 평가
        result = eval(expr, {"__builtins__": {}}, {})
        
        # 결과가 숫자인지 확인
        if isinstance(result, (int, float)):
            # 정수인 경우 정수로, 실수인 경우 적절한 형식으로 변환
            if isinstance(result, int) or result.is_integer():
                return str(int(result))
            else:
                # 소수점 이하 10자리까지 표시
                return str(round(result, 10)).rstrip('0').rstrip('.')
        else:
            return ""
            
    except (SyntaxError, NameError, TypeError, ZeroDivisionError, 
            MemoryError, OverflowError, ValueError, AttributeError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""