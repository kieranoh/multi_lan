import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    # 지원되는 연산자와 해당 함수 매핑
    OPERATORS = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv,
        '^': operator.pow,
        '%': operator.mod
    }
    
    # 연산자 우선순위
    PRECEDENCE = {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2,
        '%': 2,
        '^': 3
    }
    
    def is_number(token: str) -> bool:
        """토큰이 숫자인지 확인합니다."""
        try:
            float(token)
            return True
        except ValueError:
            return False
    
    def apply_operator(operators: list, values: list) -> None:
        """연산자 스택에서 연산자를 꺼내 값 스택에 적용합니다."""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        try:
            # 0으로 나누기 확인
            if operator_char == '/' and right == 0:
                raise ZeroDivisionError("0으로 나눌 수 없습니다.")
            
            result = OPERATORS[operator_char](left, right)
            values.append(result)
        except (ZeroDivisionError, ArithmeticError):
            raise
    
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
    
    def evaluate_postfix(postfix: list) -> float:
        """후위 표기법 표현식을 평가합니다."""
        stack = []
        
        for token in postfix:
            if isinstance(token, float):
                stack.append(token)
            elif token in OPERATORS:
                right = stack.pop()
                left = stack.pop()
                
                try:
                    # 0으로 나누기 확인
                    if token == '/' and right == 0:
                        raise ZeroDivisionError("0으로 나눌 수 없습니다.")
                    
                    result = OPERATORS[token](left, right)
                    stack.append(result)
                except (ZeroDivisionError, ArithmeticError):
                    raise
        
        if len(stack) != 1:
            raise ValueError("잘못된 표현식입니다.")
        
        return stack[0]
    
    try:
        # 입력 검증
        if not expr or not isinstance(expr, str):
            return ""
        
        # 공백 제거
        expr = expr.strip()
        if not expr:
            return ""
        
        # 표현식 토큰화
        # 정규식을 사용하여 숫자, 연산자, 괄호를 토큰으로 분리
        token_pattern = r'\d+\.?\d*|[\+\-\*\/\^%\(\)]'
        tokens = re.findall(token_pattern, expr)
        
        # 모든 문자가 토큰으로 변환되었는지 확인
        original_chars = ''.join(expr.split())
        token_chars = ''.join(tokens)
        
        # 허용되지 않는 문자가 있는지 확인
        if original_chars != token_chars:
            return ""
        
        # 후위 표기법으로 변환
        postfix = shunting_yard(tokens)
        
        # 후위 표기법 평가
        result = evaluate_postfix(postfix)
        
        # 결과를 문자열로 변환
        # 정수인 경우 소수점 없이, 실수인 경우 적절한 형식으로
        if result.is_integer():
            return str(int(result))
        else:
            # 부동소수점 오차를 줄이기 위해 반올림
            return str(round(result, 10)).rstrip('0').rstrip('.')
    
    except (ValueError, ZeroDivisionError, ArithmeticError, IndexError, KeyError):
        return ""
    except Exception:
        # 모든 다른 예외도 빈 문자열 반환
        return ""