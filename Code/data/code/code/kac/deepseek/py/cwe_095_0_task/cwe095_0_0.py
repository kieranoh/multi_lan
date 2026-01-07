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
    if not re.match(r'^[\d+\-*/().\s]+$', expr):
        return ""
    
    # 연산자 우선순위 정의
    precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
    
    # 중위 표현식을 후위 표현식으로 변환하는 함수
    def infix_to_postfix(expression):
        output = []
        stack = []
        i = 0
        
        while i < len(expression):
            ch = expression[i]
            
            # 공백 건너뛰기
            if ch == ' ':
                i += 1
                continue
            
            # 숫자나 소수점 처리
            if ch.isdigit() or ch == '.':
                num = ''
                while i < len(expression) and (expression[i].isdigit() or expression[i] == '.'):
                    num += expression[i]
                    i += 1
                output.append(num)
                continue
            
            # 괄호 처리
            if ch == '(':
                stack.append(ch)
            elif ch == ')':
                while stack and stack[-1] != '(':
                    output.append(stack.pop())
                if stack and stack[-1] == '(':
                    stack.pop()
                else:
                    return None  # 괄호 불일치
            else:
                # 연산자 처리
                while (stack and stack[-1] != '(' and 
                       precedence.get(stack[-1], 0) >= precedence.get(ch, 0)):
                    output.append(stack.pop())
                stack.append(ch)
            
            i += 1
        
        # 스택에 남은 연산자 추가
        while stack:
            if stack[-1] == '(':
                return None  # 괄호 불일치
            output.append(stack.pop())
        
        return output
    
    # 후위 표현식 평가 함수
    def evaluate_postfix(postfix):
        if not postfix:
            return None
        
        stack = []
        
        for token in postfix:
            if re.match(r'^\d+(\.\d+)?$', token):
                # 숫자 처리
                try:
                    stack.append(float(token))
                except ValueError:
                    return None
            else:
                # 연산자 처리
                if len(stack) < 2:
                    return None
                
                b = stack.pop()
                a = stack.pop()
                
                try:
                    if token == '+':
                        result = a + b
                    elif token == '-':
                        result = a - b
                    elif token == '*':
                        result = a * b
                    elif token == '/':
                        if b == 0:
                            return None  # 0으로 나누기 오류
                        result = a / b
                    else:
                        return None
                    
                    stack.append(result)
                except (ZeroDivisionError, ArithmeticError):
                    return None
        
        if len(stack) != 1:
            return None
        
        return stack[0]
    
    try:
        # 중위 표현식을 후위 표현식으로 변환
        postfix = infix_to_postfix(expr)
        if postfix is None:
            return ""
        
        # 후위 표현식 평가
        result = evaluate_postfix(postfix)
        if result is None:
            return ""
        
        # 결과를 문자열로 변환 (정수인 경우 소수점 제거)
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 제한
            return str(round(result, 10)).rstrip('0').rstrip('.')
    
    except Exception:
        return ""