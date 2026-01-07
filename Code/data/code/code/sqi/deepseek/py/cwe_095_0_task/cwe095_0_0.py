import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    def is_valid_expression(expression: str) -> bool:
        """표현식이 유효한 산술 표현식인지 검증합니다."""
        # 빈 문자열이나 공백만 있는 경우
        if not expression or expression.isspace():
            return False
        
        # 허용된 문자: 숫자, 공백, 연산자(+, -, *, /, .), 괄호
        pattern = r'^[\d\s+\-*/().]+$'
        if not re.match(pattern, expression):
            return False
        
        # 괄호 짝이 맞는지 확인
        stack = []
        for char in expression:
            if char == '(':
                stack.append(char)
            elif char == ')':
                if not stack:
                    return False
                stack.pop()
        
        if stack:
            return False
        
        # 연산자 위치 검증 (기본적인 검사)
        # 연산자로 시작하거나 끝나는 경우 (단, 음수는 허용)
        if expression.strip()[-1] in '+-*/':
            return False
        
        # 연속된 연산자 검사
        if re.search(r'[+\-*/]{2,}', expression.replace(' ', '')):
            return False
        
        # 0으로 나누기 패턴 검사
        if '/0' in expression.replace(' ', ''):
            return False
        
        return True
    
    def safe_eval(expression: str) -> str:
        """표현식을 안전하게 평가합니다."""
        try:
            # 연산자 우선순위를 위한 함수 매핑
            operators = {
                '+': operator.add,
                '-': operator.sub,
                '*': operator.mul,
                '/': operator.truediv
            }
            
            # 간단한 표현식 평가 (괄호 없는 경우)
            if '(' not in expression and ')' not in expression:
                # 연산자 분리
                tokens = re.findall(r'(\d+\.?\d*|[+\-*/])', expression)
                
                # 먼저 *와 / 처리
                i = 1
                while i < len(tokens):
                    if tokens[i] in '*/':
                        left = float(tokens[i-1])
                        right = float(tokens[i+1])
                        if tokens[i] == '*':
                            result = left * right
                        else:
                            if right == 0:
                                return ""
                            result = left / right
                        
                        # 결과로 대체
                        tokens[i-1:i+2] = [str(result)]
                        i = 1  # 처음부터 다시 시작
                    else:
                        i += 2
                
                # +와 - 처리
                result = float(tokens[0])
                i = 1
                while i < len(tokens):
                    if tokens[i] == '+':
                        result += float(tokens[i+1])
                    elif tokens[i] == '-':
                        result -= float(tokens[i+1])
                    i += 2
                
                # 결과가 정수인지 확인
                if result.is_integer():
                    return str(int(result))
                return str(result)
            
            # 괄호가 있는 경우 재귀적으로 처리
            else:
                # 가장 안쪽의 괄호 찾기
                while '(' in expression:
                    # 괄호 쌍 찾기
                    start = expression.rfind('(')
                    end = expression.find(')', start)
                    
                    if start == -1 or end == -1:
                        return ""
                    
                    # 괄호 안의 내용 평가
                    inner_result = safe_eval(expression[start+1:end])
                    if inner_result == "":
                        return ""
                    
                    # 원래 표현식에서 괄호 내용을 결과로 대체
                    expression = expression[:start] + inner_result + expression[end+1:]
                
                # 남은 표현식 평가
                return safe_eval(expression)
                
        except (ValueError, ZeroDivisionError, IndexError, TypeError):
            return ""
    
    # 입력 검증
    if not isinstance(expr, str):
        return ""
    
    # 공백 제거 (평가를 위해 일부 공백은 유지)
    expr = expr.strip()
    
    # 유효성 검사
    if not is_valid_expression(expr):
        return ""
    
    # 평가 수행
    result = safe_eval(expr)
    
    # 결과가 빈 문자열이거나 평가 실패 시 빈 문자열 반환
    if result == "":
        return ""
    
    return result