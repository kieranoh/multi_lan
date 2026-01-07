import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식.

    Returns:
        str: 산술 표현식의 결과, 또는 오류가 발생하면 빈 문자열.'''
    
    def is_valid_expression(expression: str) -> bool:
        """표현식이 안전하고 유효한 산술 표현식인지 확인합니다."""
        # 허용되는 문자: 숫자, 공백, 기본 연산자, 소수점, 괄호
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
        
        # 연산자 위치가 유효한지 확인 (간단한 검사)
        # 연산자 연속 사용 방지 (단, 음수 기호는 예외)
        cleaned = re.sub(r'\s+', '', expression)
        # 연속된 연산자 패턴 검사 (-- 같은 경우는 허용)
        if re.search(r'[\+\-\*\/]{2,}', cleaned.replace('--', '')):
            return False
        
        return True
    
    def apply_operator(operators: list, values: list):
        """연산자 스택에서 연산을 적용합니다."""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        if operator_char == '+':
            values.append(left + right)
        elif operator_char == '-':
            values.append(left - right)
        elif operator_char == '*':
            values.append(left * right)
        elif operator_char == '/':
            if right == 0:
                raise ZeroDivisionError("0으로 나눌 수 없습니다.")
            values.append(left / right)
    
    def precedence(op: str) -> int:
        """연산자 우선순위를 반환합니다."""
        if op in ('+', '-'):
            return 1
        if op in ('*', '/'):
            return 2
        return 0
    
    def evaluate_with_shunting_yard(expression: str) -> float:
        """Shunting-yard 알고리즘을 사용하여 표현식을 평가합니다."""
        # 토큰화
        tokens = re.findall(r'\d+\.?\d*|[\+\-\*\/\(\)]', expression.replace(' ', ''))
        
        values = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            # 숫자인 경우
            if re.match(r'\d+\.?\d*', token):
                values.append(float(token))
            
            # '('인 경우
            elif token == '(':
                operators.append(token)
            
            # ')'인 경우
            elif token == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                operators.pop()  # '(' 제거
            
            # 연산자인 경우
            else:
                # 음수 처리 (토큰이 '-'이고 이전 토큰이 숫자나 ')'가 아닌 경우)
                if token == '-' and (i == 0 or tokens[i-1] in '+-*/('):
                    # 다음 토큰이 숫자인지 확인
                    if i + 1 < len(tokens) and re.match(r'\d+\.?\d*', tokens[i+1]):
                        values.append(-float(tokens[i+1]))
                        i += 2
                        continue
                
                while (operators and operators[-1] != '(' and 
                       precedence(operators[-1]) >= precedence(token)):
                    apply_operator(operators, values)
                operators.append(token)
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            apply_operator(operators, values)
        
        return values[0]
    
    try:
        # 입력 검증
        if not expr or not isinstance(expr, str):
            return ""
        
        # 공백 제거 (앞뒤 공백만 제거, 내부 공백은 유지)
        expr = expr.strip()
        if not expr:
            return ""
        
        # 유효성 검사
        if not is_valid_expression(expr):
            return ""
        
        # 표현식 평가
        result = evaluate_with_shunting_yard(expr)
        
        # 결과 형식화
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 불필요한 0 제거
            result_str = str(result).rstrip('0').rstrip('.')
            return result_str
            
    except (ValueError, ZeroDivisionError, IndexError, TypeError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""