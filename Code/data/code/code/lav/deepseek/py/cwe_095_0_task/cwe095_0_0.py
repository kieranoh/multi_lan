import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    # 연산자 우선순위 정의
    PRECEDENCE = {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2,
        '^': 3  # 거듭제곱 연산자
    }
    
    # 연산자 함수 매핑
    OPERATORS = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv,
        '^': operator.pow
    }
    
    def apply_operator(operators, values):
        """연산자를 적용하여 값을 계산합니다."""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        try:
            # 0으로 나누기 체크
            if operator_char == '/' and right == 0:
                raise ZeroDivisionError("0으로 나눌 수 없습니다.")
            
            result = OPERATORS[operator_char](left, right)
            values.append(result)
        except (ZeroDivisionError, OverflowError, ValueError) as e:
            raise e
    
    def has_higher_precedence(op1, op2):
        """op1이 op2보다 높거나 같은 우선순위를 가지는지 확인합니다."""
        return PRECEDENCE.get(op1, 0) >= PRECEDENCE.get(op2, 0)
    
    def tokenize(expression):
        """표현식을 토큰으로 분리합니다."""
        # 숫자, 연산자, 괄호를 분리하는 정규식
        token_pattern = r'\d+\.?\d*|[\+\-\*\/\^\(\)]'
        tokens = re.findall(token_pattern, expression)
        
        # 음수 처리: 첫 번째 토큰이 '-'이거나 '(' 다음에 '-'가 오는 경우
        processed_tokens = []
        i = 0
        while i < len(tokens):
            if tokens[i] == '-' and (i == 0 or tokens[i-1] == '(' or tokens[i-1] in OPERATORS):
                # 음수 처리
                if i + 1 < len(tokens) and re.match(r'\d+\.?\d*', tokens[i+1]):
                    processed_tokens.append('-' + tokens[i+1])
                    i += 2
                else:
                    # 유효하지 않은 음수 표현
                    return []
            else:
                processed_tokens.append(tokens[i])
                i += 1
        
        return processed_tokens
    
    try:
        # 빈 표현식 체크
        if not expr or not expr.strip():
            return ""
        
        # 공백 제거
        expr = expr.replace(" ", "")
        
        # 토큰화
        tokens = tokenize(expr)
        if not tokens:
            return ""
        
        # 값 스택과 연산자 스택
        values = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            # 숫자인 경우
            if re.match(r'^-?\d+\.?\d*$', token):
                # 정수 또는 실수로 변환
                if '.' in token:
                    values.append(float(token))
                else:
                    values.append(int(token))
            
            # 여는 괄호인 경우
            elif token == '(':
                operators.append(token)
            
            # 닫는 괄호인 경우
            elif token == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                
                if not operators:
                    # 괄호 불일치
                    return ""
                
                # 여는 괄호 제거
                operators.pop()
            
            # 연산자인 경우
            elif token in OPERATORS:
                while (operators and operators[-1] != '(' and 
                       has_higher_precedence(operators[-1], token)):
                    apply_operator(operators, values)
                operators.append(token)
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            if operators[-1] == '(':
                # 괄호 불일치
                return ""
            apply_operator(operators, values)
        
        # 결과가 하나만 있어야 함
        if len(values) != 1:
            return ""
        
        result = values[0]
        
        # 결과가 정수인지 실수인지 확인
        if isinstance(result, float) and result.is_integer():
            result = int(result)
        
        return str(result)
        
    except (ZeroDivisionError, ValueError, TypeError, IndexError, OverflowError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""