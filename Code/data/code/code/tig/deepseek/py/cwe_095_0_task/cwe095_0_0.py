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
        
        # 허용된 문자만 포함하는지 확인: 숫자, 연산자, 공백, 소수점, 괄호
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
        
        # 연산자 위치가 올바른지 기본 검사
        # 연산자로 시작하거나 끝나는지 확인 (단, 음수는 허용)
        cleaned = expression.replace(' ', '')
        if cleaned and cleaned[0] in '*/+':
            return False
        if cleaned and cleaned[-1] in '+-*/':
            return False
        
        # 연속된 연산자 확인
        if re.search(r'[\+\-\*/]{2,}', cleaned):
            # 단, '--'는 허용 (이중 음수)
            if not re.search(r'--', cleaned):
                return False
        
        return True
    
    def tokenize(expression: str):
        """표현식을 토큰으로 분리합니다."""
        # 연산자와 피연산자를 분리
        tokens = re.findall(r'\d+\.?\d*|[\+\-\*/\(\)]', expression.replace(' ', ''))
        return tokens
    
    def infix_to_postfix(tokens):
        """중위 표기법을 후위 표기법으로 변환합니다."""
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
        output = []
        stack = []
        
        for token in tokens:
            if re.match(r'\d+\.?\d*', token):
                output.append(token)
            elif token == '(':
                stack.append(token)
            elif token == ')':
                while stack and stack[-1] != '(':
                    output.append(stack.pop())
                stack.pop()  # '(' 제거
            else:  # 연산자
                while (stack and stack[-1] != '(' and 
                       precedence.get(stack[-1], 0) >= precedence.get(token, 0)):
                    output.append(stack.pop())
                stack.append(token)
        
        while stack:
            output.append(stack.pop())
        
        return output
    
    def evaluate_postfix(postfix):
        """후위 표기법 표현식을 평가합니다."""
        stack = []
        
        for token in postfix:
            if re.match(r'\d+\.?\d*', token):
                stack.append(float(token))
            else:
                if len(stack) < 2:
                    return None
                b = stack.pop()
                a = stack.pop()
                
                if token == '+':
                    result = a + b
                elif token == '-':
                    result = a - b
                elif token == '*':
                    result = a * b
                elif token == '/':
                    if b == 0:
                        return None
                    result = a / b
                else:
                    return None
                
                stack.append(result)
        
        if len(stack) != 1:
            return None
        
        return stack[0]
    
    try:
        # 입력 검증
        if not isinstance(expr, str):
            return ""
        
        # 공백 제거 (양쪽 끝만)
        expr = expr.strip()
        
        # 유효성 검사
        if not is_valid_expression(expr):
            return ""
        
        # 토큰화
        tokens = tokenize(expr)
        if not tokens:
            return ""
        
        # 후위 표기법으로 변환
        postfix = infix_to_postfix(tokens)
        
        # 평가
        result = evaluate_postfix(postfix)
        
        if result is None:
            return ""
        
        # 결과를 문자열로 변환 (정수인 경우 소수점 제거)
        if isinstance(result, float) and result.is_integer():
            return str(int(result))
        
        # 소수점 이하 불필요한 0 제거
        result_str = str(result).rstrip('0').rstrip('.') if '.' in str(result) else str(result)
        
        return result_str
    
    except Exception:
        # 모든 예외를 잡아 빈 문자열 반환
        return ""