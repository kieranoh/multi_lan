import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    def is_valid_expression(expression: str) -> bool:
        """표현식이 안전하고 유효한지 검증합니다."""
        # 빈 문자열이나 공백만 있는 경우
        if not expression or expression.isspace():
            return False
        
        # 허용된 문자만 포함하는지 확인 (숫자, 연산자, 공백, 소수점, 괄호)
        pattern = r'^[\d\s\+\-\*\/\.\(\)]+$'
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
        
        # 연산자 위치가 유효한지 확인 (기본적인 검사)
        # 연산자로 시작하거나 끝나는 경우 (단, 음수는 허용)
        if expression.strip()[-1] in '+-*/':
            return False
        
        # 연속된 연산자 확인
        if re.search(r'[\+\-\*\/]{2,}', expression.replace(' ', '')):
            return False
        
        # 0으로 나누기 패턴 확인
        if re.search(r'/0(?!\.\d)', expression.replace(' ', '')):
            return False
        
        return True
    
    def safe_eval(expression: str) -> float:
        """표현식을 안전하게 평가합니다."""
        # 공백 제거
        expression = expression.replace(' ', '')
        
        # 연산자 우선순위 정의
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
        
        def apply_operator(operators, values):
            op = operators.pop()
            right = values.pop()
            left = values.pop()
            
            if op == '+':
                values.append(left + right)
            elif op == '-':
                values.append(left - right)
            elif op == '*':
                values.append(left * right)
            elif op == '/':
                if right == 0:
                    raise ZeroDivisionError("0으로 나눌 수 없습니다.")
                values.append(left / right)
        
        def greater_precedence(op1, op2):
            return precedence.get(op1, 0) > precedence.get(op2, 0)
        
        values = []
        operators = []
        i = 0
        
        while i < len(expression):
            # 숫자 파싱 (정수 또는 소수)
            if expression[i].isdigit() or (expression[i] == '.' and i + 1 < len(expression) and expression[i + 1].isdigit()):
                j = i
                while j < len(expression) and (expression[j].isdigit() or expression[j] == '.'):
                    j += 1
                try:
                    values.append(float(expression[i:j]))
                except ValueError:
                    raise ValueError("잘못된 숫자 형식입니다.")
                i = j
                continue
            
            # 음수 처리
            elif expression[i] == '-' and (i == 0 or expression[i - 1] in '+-*/('):
                j = i + 1
                if j < len(expression) and expression[j] == '(':
                    operators.append('-')
                    i += 1
                    continue
                while j < len(expression) and (expression[j].isdigit() or expression[j] == '.'):
                    j += 1
                try:
                    values.append(float(expression[i:j]))
                except ValueError:
                    raise ValueError("잘못된 음수 형식입니다.")
                i = j
                continue
            
            # 괄호 열기
            elif expression[i] == '(':
                operators.append('(')
            
            # 괄호 닫기
            elif expression[i] == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                operators.pop()  # '(' 제거
            
            # 연산자
            elif expression[i] in '+-*/':
                while (operators and operators[-1] != '(' and 
                       greater_precedence(operators[-1], expression[i])):
                    apply_operator(operators, values)
                operators.append(expression[i])
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            apply_operator(operators, values)
        
        return values[0] if values else 0
    
    try:
        # 입력 검증
        if not isinstance(expr, str):
            return ""
        
        # 표현식 유효성 검사
        if not is_valid_expression(expr):
            return ""
        
        # 평가 수행
        result = safe_eval(expr)
        
        # 결과 형식화
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 표시, 불필요한 0 제거
            formatted = f"{result:.10f}"
            formatted = formatted.rstrip('0').rstrip('.') if '.' in formatted else formatted
            return formatted
            
    except (ValueError, ZeroDivisionError, IndexError, TypeError):
        return ""
    except Exception:
        return ""