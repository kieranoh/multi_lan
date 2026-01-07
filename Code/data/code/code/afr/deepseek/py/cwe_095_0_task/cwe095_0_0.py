import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    # 연산자 우선순위와 연산 함수 정의
    OPERATORS = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv,
        '^': operator.pow
    }
    
    # 연산자 우선순위 (숫자가 높을수록 우선순위 높음)
    PRECEDENCE = {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2,
        '^': 3
    }
    
    def is_number(token: str) -> bool:
        """토큰이 숫자인지 확인합니다."""
        try:
            float(token)
            return True
        except ValueError:
            return False
    
    def apply_operator(operators: list, values: list):
        """스택에서 연산자를 적용합니다."""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        # 0으로 나누기 체크
        if operator_char == '/' and right == 0:
            raise ZeroDivisionError("0으로 나눌 수 없습니다.")
        
        result = OPERATORS[operator_char](left, right)
        values.append(result)
    
    def shunting_yard(tokens: list) -> list:
        """Shunting-yard 알고리즘을 사용하여 중위 표기법을 후위 표기법으로 변환합니다."""
        output = []
        operators = []
        
        for token in tokens:
            if is_number(token):
                output.append(float(token))
            elif token in OPERATORS:
                while (operators and operators[-1] != '(' and 
                       PRECEDENCE[operators[-1]] >= PRECEDENCE[token]):
                    output.append(operators.pop())
                operators.append(token)
            elif token == '(':
                operators.append(token)
            elif token == ')':
                while operators and operators[-1] != '(':
                    output.append(operators.pop())
                if not operators:
                    raise ValueError("괄호가 맞지 않습니다.")
                operators.pop()  # '(' 제거
        
        while operators:
            if operators[-1] == '(':
                raise ValueError("괄호가 맞지 않습니다.")
            output.append(operators.pop())
        
        return output
    
    def evaluate_postfix(tokens: list) -> float:
        """후위 표기법 표현식을 평가합니다."""
        values = []
        
        for token in tokens:
            if isinstance(token, float):
                values.append(token)
            else:  # 연산자
                apply_operator([token], values)
        
        if len(values) != 1:
            raise ValueError("잘못된 표현식입니다.")
        
        return values[0]
    
    try:
        # 입력 검증
        if not expr or not isinstance(expr, str):
            return ""
        
        # 공백 제거
        expr = expr.strip()
        if not expr:
            return ""
        
        # 유효한 문자 검사 (숫자, 연산자, 괄호, 공백, 소수점만 허용)
        valid_chars = r'^[0-9+\-*/^().\s]+$'
        if not re.match(valid_chars, expr):
            return ""
        
        # 토큰화
        # 정규식을 사용하여 숫자와 연산자/괄호를 분리
        token_pattern = r'\d+\.?\d*|\.\d+|[+\-*/^()]'
        tokens = re.findall(token_pattern, expr.replace(' ', ''))
        
        # 음수 처리 (단항 연산자 '-'를 처리)
        processed_tokens = []
        i = 0
        while i < len(tokens):
            token = tokens[i]
            if token == '-' and (i == 0 or tokens[i-1] in OPERATORS or tokens[i-1] == '('):
                # 단항 음수 연산자 처리
                if i + 1 < len(tokens) and is_number(tokens[i+1]):
                    processed_tokens.append('-' + tokens[i+1])
                    i += 2
                    continue
                else:
                    return ""  # 잘못된 단항 연산자
            else:
                processed_tokens.append(token)
                i += 1
        
        # 후위 표기법으로 변환
        postfix = shunting_yard(processed_tokens)
        
        # 평가
        result = evaluate_postfix(postfix)
        
        # 결과를 문자열로 변환 (불필요한 소수점 제거)
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 표시
            return f"{result:.10f}".rstrip('0').rstrip('.')
    
    except (ValueError, ZeroDivisionError, IndexError, KeyError, TypeError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""