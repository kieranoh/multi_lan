import re
import math

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식.

    Returns:
        str: 산술 표현식의 결과, 또는 오류가 발생하면 빈 문자열.'''
    
    # 입력이 문자열인지 확인
    if not isinstance(expr, str):
        return ""
    
    # 빈 문자열 또는 공백만 있는 경우 빈 문자열 반환
    expr = expr.strip()
    if not expr:
        return ""
    
    # 안전한 문자 패턴 확인 (숫자, 기본 연산자, 괄호, 공백, 소수점, 일부 수학 함수)
    safe_pattern = r'^[\d\s\+\-\*\/\(\)\.\,\^\%\sincossqrtloglntanabs]*$'
    if not re.match(safe_pattern, expr, re.IGNORECASE):
        return ""
    
    # 잠재적으로 위험한 패턴 필터링
    dangerous_patterns = [
        r'__',  # 더블 언더스코어
        r'import\s',
        r'from\s',
        r'exec\s*\(', 
        r'eval\s*\(', 
        r'compile\s*\(',
        r'open\s*\(',
        r'file\s*\(',
        r'os\.',
        r'sys\.',
        r'subprocess\.',
        r'__import__',
        r'lambda',
        r'\[.*for.*in.*\]',  # 리스트 컴프리헨션
        r'\{.*for.*in.*\}',  # 딕셔너리 컴프리헨션
        r'\(.*for.*in.*\)',  # 제너레이터 컴프리헨션
    ]
    
    for pattern in dangerous_patterns:
        if re.search(pattern, expr, re.IGNORECASE):
            return ""
    
    try:
        # 수학 함수 매핑
        math_functions = {
            'sin': math.sin,
            'cos': math.cos,
            'tan': math.tan,
            'sqrt': math.sqrt,
            'log': math.log10,  # 상용로그
            'ln': math.log,     # 자연로그
            'abs': abs,
            'pi': math.pi,
            'e': math.e
        }
        
        # 표현식 전처리
        # 1. 공백 제거 (함수명 내부 공백은 보존)
        expr_clean = expr.replace(' ', '')
        
        # 2. 수학 함수 및 상수 치환
        for func_name, func in math_functions.items():
            if func_name in ['pi', 'e']:
                # 상수 치환
                expr_clean = re.sub(rf'\b{func_name}\b', str(func), expr_clean, flags=re.IGNORECASE)
            else:
                # 함수 호출 패턴 찾기 및 치환
                pattern = rf'{func_name}\(([^)]+)\)'
                matches = re.finditer(pattern, expr_clean, re.IGNORECASE)
                
                for match in matches:
                    original = match.group(0)
                    arg = match.group(1)
                    try:
                        # 인자 평가
                        arg_value = eval(arg, {"__builtins__": {}}, {})
                        # 함수 적용
                        if func_name in ['sin', 'cos', 'tan']:
                            # 삼각함수는 라디안 단위
                            result = func(arg_value)
                        else:
                            result = func(arg_value)
                        # 결과로 치환
                        expr_clean = expr_clean.replace(original, str(result))
                    except:
                        # 함수 평가 실패 시 원래 표현식 유지
                        pass
        
        # 3. ^를 **로 변환 (지수 연산)
        expr_clean = expr_clean.replace('^', '**')
        
        # 4. % 연산자 처리 (모듈로 연산)
        expr_clean = expr_clean.replace('%', '%')
        
        # 5. 안전한 평가 환경 설정
        safe_dict = {
            '__builtins__': {},
            'abs': abs,
            'round': round,
            'min': min,
            'max': max,
            'sum': sum,
            'pow': pow,
            'divmod': divmod
        }
        
        # 6. 표현식 평가
        result = eval(expr_clean, safe_dict, {})
        
        # 7. 결과 형식화
        if isinstance(result, (int, float)):
            # 부동소수점 오차 처리
            if abs(result - round(result, 10)) < 1e-10:
                result = round(result)
            
            # 너무 큰/작은 숫자 처리
            if abs(result) > 1e15 or (abs(result) < 1e-15 and result != 0):
                return str(result)
            
            # 정수인 경우 정수로, 실수인 경우 적절한 소수점 자리수로
            if isinstance(result, int) or result.is_integer():
                return str(int(result))
            else:
                # 소수점 이하 10자리까지 표시
                formatted = f"{result:.10f}"
                # 불필요한 0 제거
                formatted = formatted.rstrip('0').rstrip('.') if '.' in formatted else formatted
                return formatted
        else:
            return ""
            
    except Exception as e:
        # 모든 예외는 빈 문자열 반환
        return ""