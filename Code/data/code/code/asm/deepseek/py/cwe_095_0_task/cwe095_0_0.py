import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    def is_valid_expression(expression: str) -> bool:
        """표현식이 유효한 산술 표현식인지 확인합니다."""
        # 빈 문자열이나 공백만 있는 경우
        if not expression or expression.isspace():
            return False
        
        # 허용된 문자: 숫자, 공백, 연산자(+, -, *, /, %), 괄호, 소수점
        pattern = r'^[\d\s\+\-\*\/\%\(\)\.]+$'
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
        
        return len(stack) == 0
    
    def tokenize(expression: str):
        """표현식을 토큰으로 분리합니다."""
        # 연산자와 피연산자를 분리
        tokens = re.findall(r'\d+\.?\d*|[\+\-\*\/\%\(\)]', expression.replace(' ', ''))
        return tokens
    
    def apply_operator(operators, values):
        """연산자를 적용합니다."""
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
        elif operator_char == '%':
            if right == 0:
                raise ZeroDivisionError("0으로 나눌 수 없습니다.")
            values.append(left % right)
    
    def has_precedence(op1, op2):
        """연산자 우선순위를 비교합니다."""
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2, '%': 2}
        return precedence[op1] >= precedence[op2]
    
    def evaluate_tokens(tokens):
        """토큰을 평가합니다."""
        values = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            if re.match(r'\d+\.?\d*', token):
                # 숫자인 경우
                if '.' in token:
                    values.append(float(token))
                else:
                    values.append(int(token))
            elif token == '(':
                operators.append(token)
            elif token == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                operators.pop()  # '(' 제거
            else:
                # 연산자인 경우
                while (operators and operators[-1] != '(' and 
                       has_precedence(operators[-1], token)):
                    apply_operator(operators, values)
                operators.append(token)
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            apply_operator(operators, values)
        
        return values[0] if values else 0
    
    try:
        # 입력 검증
        if not isinstance(expr, str):
            return ""
        
        # 공백 제거
        expr = expr.strip()
        
        # 유효성 검사
        if not is_valid_expression(expr):
            return ""
        
        # 토큰화
        tokens = tokenize(expr)
        
        # 평가
        result = evaluate_tokens(tokens)
        
        # 결과를 문자열로 변환
        if isinstance(result, float):
            # 소수점 이하 불필요한 0 제거
            result_str = str(result).rstrip('0').rstrip('.') if '.' in str(result) else str(result)
            return result_str
        else:
            return str(result)
            
    except (ValueError, ZeroDivisionError, IndexError, KeyError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""