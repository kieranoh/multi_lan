import re
import math

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    if not expr or not isinstance(expr, str):
        return ""
    
    # 공백 제거
    expr = expr.strip()
    if not expr:
        return ""
    
    # 안전한 수학 함수 딕셔너리
    safe_dict = {
        'abs': abs,
        'round': round,
        'pow': pow,
        'max': max,
        'min': min,
        'sum': sum,
        'len': len,
        'int': int,
        'float': float,
        'math': math
    }
    
    # 수학 상수 추가
    safe_dict.update({
        'pi': math.pi,
        'e': math.e,
        'inf': float('inf'),
        'nan': float('nan')
    })
    
    # 수학 함수 추가
    for func_name in ['sqrt', 'exp', 'log', 'log10', 'sin', 'cos', 'tan', 
                      'asin', 'acos', 'atan', 'sinh', 'cosh', 'tanh',
                      'degrees', 'radians', 'ceil', 'floor', 'factorial',
                      'gcd', 'isclose', 'fabs', 'trunc']:
        if hasattr(math, func_name):
            safe_dict[func_name] = getattr(math, func_name)
    
    # 안전하지 않은 문자/키워드 검사
    unsafe_patterns = [
        r'__',  # 더블 언더스코어 (매직 메서드)
        r'import\s+',
        r'exec\s*\(', 
        r'eval\s*\(',
        r'compile\s*\(',
        r'open\s*\(',
        r'file\s*\(',
        r'input\s*\(',
        r'os\.',
        r'sys\.',
        r'subprocess\.',
        r'\.__',
        r'lambda\s+',
        r'def\s+',
        r'class\s+',
        r'raise\s+',
        r'assert\s+',
        r'del\s+',
        r'global\s+',
        r'nonlocal\s+',
        r'yield\s+',
        r'async\s+',
        r'await\s+',
        r'with\s+',
        r'from\s+',
        r'as\s+',
        r'except\s+',
        r'finally\s+',
        r'try\s+',
        r'while\s+',
        r'for\s+',
        r'if\s+',
        r'else\s+',
        r'elif\s+',
        r'pass\s+',
        r'break\s+',
        r'continue\s+',
        r'return\s+',
        r'print\s*\(',
        r'quit\s*\(',
        r'exit\s*\(',
        r'help\s*\(',
        r'license\s*\(',
        r'copyright\s*\(',
        r'credits\s*\(',
        r'locals\s*\(',
        r'globals\s*\(',
        r'vars\s*\(',
        r'dir\s*\(',
        r'type\s*\(',
        r'isinstance\s*\(',
        r'issubclass\s*\(',
        r'hasattr\s*\(',
        r'getattr\s*\(',
        r'setattr\s*\(',
        r'delattr\s*\(',
        r'callable\s*\(',
        r'property\s*\(',
        r'super\s*\(',
        r'object\s*\(',
        r'str\s*\(',
        r'repr\s*\(',
        r'format\s*\(',
        r'bytes\s*\(',
        r'bytearray\s*\(',
        r'memoryview\s*\(',
        r'slice\s*\(',
        r'range\s*\(',
        r'enumerate\s*\(',
        r'zip\s*\(',
        r'map\s*\(',
        r'filter\s*\(',
        r'reduce\s*\(',
        r'sorted\s*\(',
        r'reversed\s*\(',
        r'iter\s*\(',
        r'next\s*\(',
        r'hash\s*\(',
        r'id\s*\(',
        r'bin\s*\(',
        r'oct\s*\(',
        r'hex\s*\(',
        r'ord\s*\(',
        r'chr\s*\(',
        r'ascii\s*\(',
        r'bool\s*\(',
        r'complex\s*\(',
        r'divmod\s*\(',
        r'all\s*\(',
        r'any\s*\(',
        r'[''\"].*[''\"]\.',  # 문자열 메서드 호출
        r'\[.*\]\.',  # 리스트 메서드 호출
        r'\{.*\}\.',  # 딕셔너리 메서드 호출
        r'\(.*\)\.',  # 튜플 메서드 호출
    ]
    
    expr_lower = expr.lower()
    for pattern in unsafe_patterns:
        if re.search(pattern, expr_lower, re.IGNORECASE):
            return ""
    
    # 괄호 짝 검사
    stack = []
    for char in expr:
        if char == '(':
            stack.append(char)
        elif char == ')':
            if not stack:
                return ""
            stack.pop()
    
    if stack:
        return ""
    
    try:
        # 표현식 평가
        result = eval(expr, {"__builtins__": {}}, safe_dict)
        
        # 결과 타입 검사 및 문자열 변환
        if isinstance(result, (int, float, complex)):
            # 복소수 처리
            if isinstance(result, complex):
                # 허수부가 0이면 실수로 처리
                if result.imag == 0:
                    result = result.real
                else:
                    # 복소수 형식으로 반환
                    return f"{result.real}{'+' if result.imag >= 0 else ''}{result.imag}j"
            
            # 무한대 또는 NaN 처리
            if math.isinf(result):
                return "inf" if result > 0 else "-inf"
            if math.isnan(result):
                return "nan"
            
            # 정수인 경우 정수로, 실수인 경우 소수점 처리
            if isinstance(result, int) or (isinstance(result, float) and result.is_integer()):
                return str(int(result))
            else:
                # 소수점 이하 10자리까지 표시 (필요시 조정 가능)
                return format(result, '.10g').rstrip('0').rstrip('.')
        else:
            # 숫자 타입이 아닌 경우 빈 문자열 반환
            return ""
            
    except Exception:
        # 모든 예외 발생 시 빈 문자열 반환
        return ""