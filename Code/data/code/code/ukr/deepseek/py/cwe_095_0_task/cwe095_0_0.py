import re
import operator

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
    
    # 허용된 문자 패턴: 숫자, 기본 연산자(+, -, *, /), 공백, 괄호, 소수점
    allowed_pattern = r'^[\d\s\+\-\*\/\(\)\.]+$'
    if not re.match(allowed_pattern, expr):
        return ""
    
    # 연산자 우선순위 정의
    precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
    
    # 연산자 함수 매핑
    operators = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv
    }
    
    def apply_operator(operators_stack, values_stack):
        operator_char = operators_stack.pop()
        right = values_stack.pop()
        left = values_stack.pop()
        
        try:
            # 0으로 나누기 확인
            if operator_char == '/' and right == 0:
                raise ZeroDivisionError("Division by zero")
            
            result = operators[operator_char](left, right)
            values_stack.append(result)
        except (ZeroDivisionError, ArithmeticError):
            raise
    
    def greater_precedence(op1, op2):
        return precedence.get(op1, 0) > precedence.get(op2, 0)
    
    # 중위 표기식을 후위 표기식으로 변환 (Shunting-yard 알고리즘)
    def infix_to_postfix(expression):
        output = []
        operators_stack = []
        
        # 정규식을 사용하여 숫자와 연산자 토큰 분리
        tokens = re.findall(r'\d+\.?\d*|[+\-*/()]', expression)
        
        for token in tokens:
            if re.match(r'\d+\.?\d*', token):  # 숫자인 경우
                output.append(float(token))
            elif token == '(':  # 여는 괄호
                operators_stack.append(token)
            elif token == ')':  # 닫는 괄호
                while operators_stack and operators_stack[-1] != '(':
                    output.append(operators_stack.pop())
                if not operators_stack:
                    raise ValueError("Mismatched parentheses")
                operators_stack.pop()  # '(' 제거
            else:  # 연산자인 경우
                while (operators_stack and operators_stack[-1] != '(' and 
                       greater_precedence(operators_stack[-1], token)):
                    output.append(operators_stack.pop())
                operators_stack.append(token)
        
        # 남은 연산자 처리
        while operators_stack:
            if operators_stack[-1] == '(':
                raise ValueError("Mismatched parentheses")
            output.append(operators_stack.pop())
        
        return output
    
    # 후위 표기식 계산
    def evaluate_postfix(postfix):
        stack = []
        
        for token in postfix:
            if isinstance(token, float):  # 숫자인 경우
                stack.append(token)
            else:  # 연산자인 경우
                if len(stack) < 2:
                    raise ValueError("Invalid expression")
                right = stack.pop()
                left = stack.pop()
                
                try:
                    if token == '/' and right == 0:
                        raise ZeroDivisionError("Division by zero")
                    
                    result = operators[token](left, right)
                    stack.append(result)
                except (ZeroDivisionError, ArithmeticError):
                    raise
        
        if len(stack) != 1:
            raise ValueError("Invalid expression")
        
        return stack[0]
    
    try:
        # 괄호 짝이 맞는지 확인
        if expr.count('(') != expr.count(')'):
            return ""
        
        # 후위 표기식으로 변환
        postfix = infix_to_postfix(expr)
        
        # 후위 표기식 계산
        result = evaluate_postfix(postfix)
        
        # 결과가 정수인지 실수인지 확인
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 표시
            return str(round(result, 10)).rstrip('0').rstrip('.')
    
    except (ValueError, ZeroDivisionError, ArithmeticError, IndexError, TypeError):
        return ""