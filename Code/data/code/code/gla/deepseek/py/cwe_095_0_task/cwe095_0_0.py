import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    # 입력이 문자열인지 확인
    if not isinstance(expr, str):
        return ""
    
    # 빈 문자열 또는 공백만 있는 경우 빈 문자열 반환
    if not expr or expr.isspace():
        return ""
    
    # 허용된 문자 패턴: 숫자, 공백, 기본 산술 연산자(+, -, *, /, %, ^), 괄호, 소수점
    # 음수 처리를 위해 첫 번째 문자나 괄호 뒤에 오는 -는 허용
    pattern = r'^[\d\s\+\-\*\/\%\^\(\)\.]+$'
    
    # 표현식에 허용되지 않은 문자가 있는지 확인
    if not re.match(pattern, expr):
        return ""
    
    # 연산자 우선순위 정의
    precedence = {
        '^': 4,
        '*': 3,
        '/': 3,
        '%': 3,
        '+': 2,
        '-': 2,
        '(': 1
    }
    
    # 연산자 함수 매핑
    operations = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv,
        '%': operator.mod,
        '^': operator.pow
    }
    
    def apply_operator(operators, values):
        """연산자를 적용하여 값을 계산합니다."""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        try:
            # 0으로 나누기 방지
            if operator_char == '/' and right == 0:
                raise ZeroDivisionError("0으로 나눌 수 없습니다.")
            
            # 모듈로 연산에서 0으로 나누기 방지
            if operator_char == '%' and right == 0:
                raise ZeroDivisionError("0으로 모듈로 연산할 수 없습니다.")
            
            result = operations[operator_char](left, right)
            values.append(result)
        except (ZeroDivisionError, ValueError, ArithmeticError):
            raise
    
    def is_higher_precedence(op1, op2):
        """op1이 op2보다 높은 우선순위를 가지는지 확인합니다."""
        return precedence[op1] > precedence[op2]
    
    def tokenize(expression):
        """표현식을 토큰으로 분리합니다."""
        tokens = []
        i = 0
        length = len(expression)
        
        while i < length:
            char = expression[i]
            
            # 숫자 또는 소수점 처리
            if char.isdigit() or char == '.':
                num = char
                i += 1
                while i < length and (expression[i].isdigit() or expression[i] == '.'):
                    num += expression[i]
                    i += 1
                
                # 유효한 숫자인지 확인
                try:
                    # 소수점이 여러 개 있는지 확인
                    if num.count('.') > 1:
                        return None
                    tokens.append(float(num))
                except ValueError:
                    return None
                continue
            
            # 연산자 또는 괄호 처리
            elif char in '+-*/%^()':
                # 음수 처리: 첫 번째 토큰이거나 이전 토큰이 연산자 또는 여는 괄호인 경우
                if char == '-' and (not tokens or 
                                   (isinstance(tokens[-1], str) and tokens[-1] in '+-*/%^(')):
                    # 다음 문자가 숫자나 여는 괄호인지 확인
                    if i + 1 < length and (expression[i+1].isdigit() or expression[i+1] == '(' or expression[i+1] == '.'):
                        num = '-'
                        i += 1
                        # 다음 문자가 여는 괄호인 경우
                        if expression[i] == '(':
                            tokens.append(char)  # 단항 마이너스 연산자로 처리
                            continue
                        # 숫자 처리
                        while i < length and (expression[i].isdigit() or expression[i] == '.'):
                            num += expression[i]
                            i += 1
                        
                        try:
                            if num.count('.') > 1:
                                return None
                            tokens.append(float(num))
                        except ValueError:
                            return None
                        continue
                
                tokens.append(char)
                i += 1
                continue
            
            # 공백은 무시
            elif char.isspace():
                i += 1
                continue
            
            # 허용되지 않은 문자
            else:
                return None
        
        return tokens
    
    # 표현식 토큰화
    tokens = tokenize(expr)
    if tokens is None:
        return ""
    
    # 연산자 스택과 값 스택 초기화
    operators = []
    values = []
    
    try:
        for token in tokens:
            # 숫자인 경우
            if isinstance(token, (int, float)):
                values.append(token)
            
            # 여는 괄호인 경우
            elif token == '(':
                operators.append(token)
            
            # 닫는 괄호인 경우
            elif token == ')':
                # 여는 괄호를 만날 때까지 모든 연산자 적용
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                
                # 여는 괄호 제거
                if operators and operators[-1] == '(':
                    operators.pop()
                else:
                    # 괄호 불일치
                    return ""
            
            # 연산자인 경우
            else:
                # 현재 연산자보다 높은 우선순위의 연산자를 모두 적용
                while (operators and operators[-1] != '(' and 
                       is_higher_precedence(operators[-1], token)):
                    apply_operator(operators, values)
                
                operators.append(token)
        
        # 남은 모든 연산자 적용
        while operators:
            # 괄호 불일치 확인
            if operators[-1] == '(':
                return ""
            apply_operator(operators, values)
        
        # 결과가 하나만 남아 있어야 함
        if len(values) != 1:
            return ""
        
        result = values[0]
        
        # 결과가 정수인 경우 정수로 변환
        if isinstance(result, float) and result.is_integer():
            result = int(result)
        
        return str(result)
    
    except (ZeroDivisionError, ValueError, ArithmeticError, IndexError, KeyError):
        return ""