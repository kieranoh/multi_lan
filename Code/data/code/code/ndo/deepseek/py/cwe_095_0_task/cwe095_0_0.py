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
    
    # 허용된 문자 패턴: 숫자, 연산자(+, -, *, /), 공백, 괄호, 소수점
    if not re.match(r'^[\d\s\+\-\*\/\(\)\.]+$', expr):
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
        """연산자를 적용하여 값을 계산합니다."""
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
    
    def greater_precedence(op1, op2):
        """op1이 op2보다 높거나 같은 우선순위를 가지는지 확인합니다."""
        return precedence.get(op1, 0) >= precedence.get(op2, 0)
    
    # 중위 표현식을 후위 표현식으로 변환 (Shunting-yard 알고리즘)
    def infix_to_postfix(expression):
        """중위 표현식을 후위 표현식으로 변환합니다."""
        output = []
        operators = []
        i = 0
        length = len(expression)
        
        while i < length:
            char = expression[i]
            
            # 공백 건너뛰기
            if char == ' ':
                i += 1
                continue
            
            # 숫자 처리 (정수 및 소수)
            if char.isdigit() or char == '.':
                num_str = ''
                while i < length and (expression[i].isdigit() or expression[i] == '.'):
                    num_str += expression[i]
                    i += 1
                
                # 유효한 숫자인지 확인
                try:
                    # 소수점이 여러 개 있는지 확인
                    if num_str.count('.') > 1:
                        return None
                    output.append(float(num_str) if '.' in num_str else int(num_str))
                except ValueError:
                    return None
                continue
            
            # 왼쪽 괄호 처리
            elif char == '(':
                operators.append(char)
            
            # 오른쪽 괄호 처리
            elif char == ')':
                while operators and operators[-1] != '(':
                    output.append(operators.pop())
                if not operators or operators[-1] != '(':
                    return None  # 괄호 불일치
                operators.pop()  # '(' 제거
            
            # 연산자 처리
            elif char in precedence:
                # 단항 마이너스 처리 (표현식 시작 또는 '(' 다음에 오는 '-')
                if char == '-' and (i == 0 or expression[i-1] == '(' or 
                                   (i > 0 and expression[i-1] in precedence and expression[i-1] != ')')):
                    # 다음 토큰이 숫자인지 확인
                    j = i + 1
                    while j < length and expression[j] == ' ':
                        j += 1
                    
                    if j < length and (expression[j].isdigit() or expression[j] == '.'):
                        num_str = '-'
                        j = i + 1
                        while j < length and (expression[j].isdigit() or expression[j] == '.' or expression[j] == ' '):
                            if expression[j] != ' ':
                                num_str += expression[j]
                            j += 1
                        
                        try:
                            output.append(float(num_str) if '.' in num_str else int(num_str))
                        except ValueError:
                            return None
                        
                        i = j
                        continue
                
                while (operators and operators[-1] != '(' and 
                       greater_precedence(operators[-1], char)):
                    output.append(operators.pop())
                operators.append(char)
            
            else:
                return None  # 유효하지 않은 문자
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            if operators[-1] == '(':
                return None  # 괄호 불일치
            output.append(operators.pop())
        
        return output
    
    # 후위 표현식 계산
    def evaluate_postfix(postfix):
        """후위 표현식을 계산합니다."""
        if not postfix:
            return None
        
        stack = []
        
        for token in postfix:
            if isinstance(token, (int, float)):
                stack.append(token)
            else:  # 연산자
                if len(stack) < 2:
                    return None
                right = stack.pop()
                left = stack.pop()
                
                try:
                    if token == '+':
                        result = left + right
                    elif token == '-':
                        result = left - right
                    elif token == '*':
                        result = left * right
                    elif token == '/':
                        if right == 0:
                            return None
                        result = left / right
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
        
        # 후위 표현식 계산
        result = evaluate_postfix(postfix)
        if result is None:
            return ""
        
        # 결과 형식화
        # 정수인 경우 소수점 없이, 실수인 경우 적절히 표시
        if isinstance(result, int) or result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 표시하고 불필요한 0 제거
            formatted = f"{result:.10f}"
            formatted = formatted.rstrip('0').rstrip('.') if '.' in formatted else formatted
            return formatted
    
    except Exception:
        return ""