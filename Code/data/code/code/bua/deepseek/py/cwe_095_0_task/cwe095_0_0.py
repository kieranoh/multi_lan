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
    
    # 허용된 문자 패턴: 숫자, 연산자(+, -, *, /, %), 괄호, 공백, 소수점
    allowed_pattern = r'^[\d\s\+\-\*\/\%\(\)\.]+$'
    if not re.match(allowed_pattern, expr):
        return ""
    
    # 연산자 우선순위 정의
    precedence = {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2,
        '%': 2
    }
    
    # 연산자 함수 매핑
    operations = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv,
        '%': operator.mod
    }
    
    def apply_operator(operators, values):
        """연산자 스택에서 연산자를 꺼내 값 스택에 적용"""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        try:
            # 0으로 나누기 방지
            if operator_char == '/' and right == 0:
                raise ZeroDivisionError("Division by zero")
            if operator_char == '%' and right == 0:
                raise ZeroDivisionError("Modulo by zero")
            
            result = operations[operator_char](left, right)
            values.append(result)
        except (ZeroDivisionError, ArithmeticError):
            raise
    
    def shunting_yard(tokens):
        """Shunting-yard 알고리즘을 사용하여 중위 표현식을 후위 표현식으로 변환"""
        output = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            # 숫자인 경우
            if token.replace('.', '', 1).isdigit():
                output.append(float(token) if '.' in token else int(token))
            
            # 연산자인 경우
            elif token in precedence:
                while (operators and operators[-1] != '(' and 
                       precedence[operators[-1]] >= precedence[token]):
                    output.append(operators.pop())
                operators.append(token)
            
            # 왼쪽 괄호인 경우
            elif token == '(':
                operators.append(token)
            
            # 오른쪽 괄호인 경우
            elif token == ')':
                while operators and operators[-1] != '(':
                    output.append(operators.pop())
                
                if not operators:
                    raise ValueError("Mismatched parentheses")
                
                operators.pop()  # '(' 제거
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            if operators[-1] == '(':
                raise ValueError("Mismatched parentheses")
            output.append(operators.pop())
        
        return output
    
    def evaluate_postfix(postfix):
        """후위 표현식 평가"""
        stack = []
        
        for token in postfix:
            if isinstance(token, (int, float)):
                stack.append(token)
            else:  # 연산자
                if len(stack) < 2:
                    raise ValueError("Invalid expression")
                
                right = stack.pop()
                left = stack.pop()
                
                try:
                    # 0으로 나누기 방지
                    if token == '/' and right == 0:
                        raise ZeroDivisionError("Division by zero")
                    if token == '%' and right == 0:
                        raise ZeroDivisionError("Modulo by zero")
                    
                    result = operations[token](left, right)
                    stack.append(result)
                except (ZeroDivisionError, ArithmeticError):
                    raise
        
        if len(stack) != 1:
            raise ValueError("Invalid expression")
        
        return stack[0]
    
    try:
        # 토큰화
        token_pattern = r'(\d+\.?\d*|[\+\-\*\/\%\(\)])'
        tokens = re.findall(token_pattern, expr.replace(' ', ''))
        
        # 토큰이 없는 경우
        if not tokens:
            return ""
        
        # 유효성 검사: 괄호 짝이 맞는지 확인
        paren_count = 0
        for token in tokens:
            if token == '(':
                paren_count += 1
            elif token == ')':
                paren_count -= 1
                if paren_count < 0:
                    return ""
        
        if paren_count != 0:
            return ""
        
        # 후위 표현식으로 변환
        postfix = shunting_yard(tokens)
        
        # 후위 표현식 평가
        result = evaluate_postfix(postfix)
        
        # 결과가 정수인지 실수인지 확인
        if isinstance(result, float) and result.is_integer():
            result = int(result)
        
        return str(result)
    
    except (ValueError, ZeroDivisionError, ArithmeticError, KeyError, IndexError):
        return ""