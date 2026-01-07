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
        
        # 허용된 문자: 숫자, 연산자(+-*/), 공백, 괄호, 소수점
        pattern = r'^[\d+\-*/().\s]+$'
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
        
        # 연산자 위치가 올바른지 기본 검사
        # 연산자 연속 사용 방지 (단, 음수는 허용)
        operators = set('+-*/')
        for i in range(len(expression) - 1):
            if expression[i] in operators and expression[i + 1] in operators:
                # 음수 기호는 허용 (예: "5*-3"은 허용, "5*/3"은 불허)
                if expression[i + 1] != '-':
                    return False
        
        return True
    
    def tokenize(expression: str):
        """표현식을 토큰으로 분리합니다."""
        tokens = []
        current = ''
        
        for char in expression:
            if char.isdigit() or char == '.':
                current += char
            else:
                if current:
                    tokens.append(current)
                    current = ''
                if char != ' ':
                    tokens.append(char)
        
        if current:
            tokens.append(current)
        
        return tokens
    
    def shunting_yard(tokens):
        """Shunting-yard 알고리즘을 사용하여 중위 표기법을 후위 표기법으로 변환합니다."""
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
        output = []
        stack = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            if re.match(r'^\d+(\.\d+)?$', token):
                output.append(token)
            elif token in precedence:
                while (stack and stack[-1] != '(' and 
                       precedence.get(stack[-1], 0) >= precedence[token]):
                    output.append(stack.pop())
                stack.append(token)
            elif token == '(':
                stack.append(token)
            elif token == ')':
                while stack and stack[-1] != '(':
                    output.append(stack.pop())
                if stack and stack[-1] == '(':
                    stack.pop()
                else:
                    raise ValueError("Mismatched parentheses")
            i += 1
        
        while stack:
            if stack[-1] == '(':
                raise ValueError("Mismatched parentheses")
            output.append(stack.pop())
        
        return output
    
    def evaluate_postfix(tokens):
        """후위 표기법 표현식을 평가합니다."""
        stack = []
        operations = {
            '+': operator.add,
            '-': operator.sub,
            '*': operator.mul,
            '/': operator.truediv
        }
        
        for token in tokens:
            if re.match(r'^\d+(\.\d+)?$', token):
                stack.append(float(token))
            elif token in operations:
                if len(stack) < 2:
                    raise ValueError("Invalid expression")
                b = stack.pop()
                a = stack.pop()
                
                if token == '/' and b == 0:
                    raise ZeroDivisionError("Division by zero")
                
                result = operations[token](a, b)
                stack.append(result)
            else:
                raise ValueError(f"Unknown token: {token}")
        
        if len(stack) != 1:
            raise ValueError("Invalid expression")
        
        return stack[0]
    
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
        
        # 후위 표기법으로 변환
        postfix = shunting_yard(tokens)
        
        # 평가
        result = evaluate_postfix(postfix)
        
        # 결과 형식화
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 표시
            return f"{result:.10f}".rstrip('0').rstrip('.')
    
    except (ValueError, ZeroDivisionError, IndexError, TypeError, 
            AttributeError, KeyError, OverflowError):
        return ""