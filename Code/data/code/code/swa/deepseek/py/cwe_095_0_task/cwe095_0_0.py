import re
import math

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    def safe_eval(expression: str) -> float:
        """안전하게 수학 표현식을 평가합니다."""
        # 허용된 수학 함수와 상수
        allowed_names = {
            'abs': abs, 'round': round, 'min': min, 'max': max,
            'pow': pow, 'sqrt': math.sqrt, 'log': math.log,
            'log10': math.log10, 'exp': math.exp, 'sin': math.sin,
            'cos': math.cos, 'tan': math.tan, 'pi': math.pi,
            'e': math.e
        }
        
        # 표현식 검증
        code = compile(expression, "<string>", "eval")
        for name in code.co_names:
            if name not in allowed_names:
                raise NameError(f"사용할 수 없는 함수 또는 변수: {name}")
        return eval(code, {"__builtins__": {}}, allowed_names)
    
    try:
        # 입력 검증
        if not expr or not isinstance(expr, str):
            return ""
        
        # 공백 제거
        expr = expr.strip()
        
        # 빈 문자열 체크
        if not expr:
            return ""
        
        # 잠재적으로 위험한 패턴 필터링
        dangerous_patterns = [
            r'__.*__',  # 매직 메서드
            r'import\s+',  # import 문
            r'open\s*\(',  # 파일 열기
            r'eval\s*\(',  # eval 호출
            r'exec\s*\(',  # exec 호출
            r'compile\s*\(',  # compile 호출
            r'\.\s*[a-zA-Z_][a-zA-Z0-9_]*\s*\(',  # 메서드 호출
        ]
        
        for pattern in dangerous_patterns:
            if re.search(pattern, expr, re.IGNORECASE):
                return ""
        
        # 안전한 연산자와 함수만 허용
        # 허용된 문자: 숫자, 연산자, 괄호, 공백, 수학 함수 이름
        safe_pattern = r'^[\d\s\+\-\*\/\(\)\.\,\^\%\sabs|round|min|max|pow|sqrt|log|log10|exp|sin|cos|tan|pi|e]+$'
        
        # ^ 연산자를 **로 변환 (거듭제곱)
        expr = expr.replace('^', '**')
        
        # 수학 표현식 평가
        result = safe_eval(expr)
        
        # 결과를 문자열로 변환
        # 정수인 경우 소수점 없이, 실수인 경우 적절한 형식으로
        if isinstance(result, (int, float)):
            if result == int(result):
                return str(int(result))
            else:
                # 너무 긴 소수점은 제한
                result_str = str(round(result, 10))
                # 불필요한 0 제거
                if '.' in result_str:
                    result_str = result_str.rstrip('0').rstrip('.')
                return result_str
        else:
            return ""
            
    except (SyntaxError, NameError, TypeError, ValueError, 
            ZeroDivisionError, OverflowError, MemoryError,
            AttributeError, KeyError, IndexError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""
    except Exception:
        # 기타 모든 예외
        return ""