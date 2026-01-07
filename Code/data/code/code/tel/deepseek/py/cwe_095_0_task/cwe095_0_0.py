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
    
    # 허용된 문자 패턴: 숫자, 기본 연산자(+, -, *, /), 공백, 소수점, 괄호
    allowed_pattern = r'^[\d+\-*/().\s]+$'
    if not re.match(allowed_pattern, expr):
        return ""
    
    # 연산자 우선순위 정의
    precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
    
    # 연산자 함수 매핑
    operations = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv
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
            
            if token.replace('.', '', 1).isdigit() or (token.startswith('-') and token[1:].replace('.', '', 1).isdigit() and (i == 0 or tokens[i-1] == '(' or tokens[i-1] in '+-*/')):
                # 숫자 처리 (음수 포함)
                output.append(float(token))
            
            elif token in '+-*/':
                # 연산자 처리
                while (operators and operators[-1] != '(' and 
                       precedence[operators[-1]] >= precedence[token]):
                    output.append(operators.pop())
                operators.append(token)
            
            elif token == '(':
                operators.append(token)
            
            elif token == ')':
                # 닫는 괄호 처리
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
            if isinstance(token, float):
                stack.append(token)
            else:
                # 연산자 처리
                right = stack.pop()
                left = stack.pop()
                
                if token == '/' and right == 0:
                    raise ZeroDivisionError("Division by zero")
                
                result = operations[token](left, right)
                stack.append(result)
        
        return stack[0] if stack else 0
    
    try:
        # 토큰화
        tokens = []
        i = 0
        while i < len(expr):
            char = expr[i]
            
            if char.isdigit() or char == '.':
                # 숫자나 소수점 처리
                num = char
                i += 1
                while i < len(expr) and (expr[i].isdigit() or expr[i] == '.'):
                    num += expr[i]
                    i += 1
                
                # 유효한 숫자인지 확인
                try:
                    float(num)
                    tokens.append(num)
                except ValueError:
                    return ""
                
                continue
            
            elif char in '+-*/()':
                # 연산자나 괄호 처리
                # 음수 부호 처리
                if char == '-' and (i == 0 or expr[i-1] in '+-*/('):
                    # 다음 문자가 숫자인지 확인
                    if i + 1 < len(expr) and (expr[i+1].isdigit() or expr[i+1] == '.'):
                        num = '-'
                        i += 1
                        while i < len(expr) and (expr[i].isdigit() or expr[i] == '.'):
                            num += expr[i]
                            i += 1
                        
                        try:
                            float(num)
                            tokens.append(num)
                        except ValueError:
                            return ""
                        
                        continue
                
                tokens.append(char)
                i += 1
            
            elif char.isspace():
                # 공백 무시
                i += 1
            
            else:
                # 허용되지 않은 문자
                return ""
        
        # 토큰이 없는 경우
        if not tokens:
            return ""
        
        # 후위 표현식으로 변환
        postfix = shunting_yard(tokens)
        
        # 후위 표현식 평가
        result = evaluate_postfix(postfix)
        
        # 결과를 문자열로 변환 (불필요한 소수점 제거)
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 제한
            return f"{result:.10f}".rstrip('0').rstrip('.')
    
    except (ValueError, ZeroDivisionError, IndexError, KeyError, ArithmeticError):
        return ""