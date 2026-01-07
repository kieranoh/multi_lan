import re
import math

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    def safe_eval(expression: str) -> str:
        """안전하게 수식 평가를 수행하는 내부 함수"""
        try:
            # 빈 문자열이나 None 체크
            if not expr or expr.strip() == "":
                return ""
            
            # 입력 문자열 정리
            expr_clean = expr.strip()
            
            # 잠재적으로 위험한 문자나 함수 필터링
            # 허용할 문자: 숫자, 기본 연산자, 괄호, 공백, 소수점
            allowed_pattern = r'^[\d\s\+\-\*\/\(\)\.\^\%\s]+$'
            
            # ^ 연산자를 **로 변환 (지수 연산)
            expr_clean = expr_clean.replace('^', '**')
            
            # % 연산자가 모듈로 연산인지 퍼센트인지 확인
            # 단순한 패턴 매칭으로 %가 퍼센트인 경우 처리
            percent_pattern = r'(\d+(?:\.\d+)?)\s*\%'
            percent_matches = re.findall(percent_pattern, expr_clean)
            
            # 퍼센트를 소수로 변환
            for percent in percent_matches:
                expr_clean = expr_clean.replace(f'{percent}%', f'({percent}/100)')
            
            # 허용되지 않은 문자가 있는지 확인
            if not re.match(allowed_pattern, expr_clean.replace('**', '')):
                return ""
            
            # 수학 함수나 내장 함수 사용 방지
            # eval에 전달할 네임스페이스를 제한
            allowed_names = {
                '__builtins__': None,
                'math': None
            }
            
            # 실제 평가 수행
            result = eval(expr_clean, allowed_names)
            
            # 결과가 숫자인지 확인
            if isinstance(result, (int, float)):
                # 정수인 경우 정수로, 소수인 경우 적절히 포맷팅
                if result == int(result):
                    return str(int(result))
                else:
                    # 소수점 이하 10자리까지 제한
                    return format(result, '.10f').rstrip('0').rstrip('.')
            else:
                return ""
                
        except ZeroDivisionError:
            # 0으로 나누기 오류 처리
            return ""
        except (SyntaxError, NameError, TypeError, ValueError, MemoryError):
            # 기타 평가 오류 처리
            return ""
        except Exception:
            # 모든 다른 예외 처리
            return ""
    
    # 안전한 평가 실행
    return safe_eval(expr)