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
    
    # 입력 문자열 정리
    expr = expr.strip()
    
    # 빈 문자열 확인
    if not expr:
        return ""
    
    # 허용된 문자 패턴: 숫자, 기본 연산자, 공백, 괄호
    allowed_pattern = r'^[\d\s\+\-\*\/\(\)\.]+$'
    if not re.match(allowed_pattern, expr):
        return ""
    
    # 연산자 우선순위 매핑
    precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
    
    # 중위 표현식을 후위 표현식으로 변환 (Shunting-yard 알고리즘)
    def infix_to_postfix(expression):
        output = []
        operators = []
        
        # 토큰화
        tokens = re.findall(r'\d+\.?\d*|[+\-*/()]', expression)
        
        for token in tokens:
            if re.match(r'\d+\.?\d*', token):
                output.append(token)
            elif token == '(':
                operators.append(token)
            elif token == ')':
                while operators and operators[-1] != '(':
                    output.append(operators.pop())
                if operators and operators[-1] == '(':
                    operators.pop()
                else:
                    return None  # 괄호 불일치
            else:  # 연산자
                while (operators and operators[-1] != '(' and 
                       precedence.get(operators[-1], 0) >= precedence.get(token, 0)):
                    output.append(operators.pop())
                operators.append(token)
        
        while operators:
            if operators[-1] == '(':
                return None  # 괄호 불일치
            output.append(operators.pop())
        
        return output
    
    # 후위 표현식 평가
    def evaluate_postfix(postfix):
        if not postfix:
            return None
        
        stack = []
        operations = {
            '+': operator.add,
            '-': operator.sub,
            '*': operator.mul,
            '/': operator.truediv
        }
        
        for token in postfix:
            if re.match(r'\d+\.?\d*', token):
                try:
                    # 정수 또는 부동소수점으로 변환
                    if '.' in token:
                        stack.append(float(token))
                    else:
                        stack.append(int(token))
                except ValueError:
                    return None
            else:  # 연산자
                if len(stack) < 2:
                    return None
                b = stack.pop()
                a = stack.pop()
                
                # 0으로 나누기 확인
                if token == '/' and b == 0:
                    return None
                
                try:
                    result = operations[token](a, b)
                    stack.append(result)
                except (ZeroDivisionError, KeyError):
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
        
        # 결과를 문자열로 변환
        if isinstance(result, float):
            # 소수점 이하 불필요한 0 제거
            result_str = str(result).rstrip('0').rstrip('.') if '.' in str(result) else str(result)
            return result_str
        else:
            return str(result)
            
    except Exception:
        return ""