import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식.

    Returns:
        str: 산술 표현식의 결과, 또는 오류가 발생하면 빈 문자열.'''
    
    def is_valid_expression(expression: str) -> bool:
        """표현식이 유효한 산술 표현식인지 검증합니다."""
        # 빈 문자열이나 공백만 있는 경우
        if not expression or expression.isspace():
            return False
        
        # 허용된 문자: 숫자, 공백, 연산자(+, -, *, /, .), 괄호
        pattern = r'^[0-9+\-*/().\s]+$'
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
        
        # 연산자 패턴 검증 (연속된 연산자 방지, 단 음수 부호는 예외)
        # 간단한 검증: 표현식이 숫자로 시작하고 끝나야 함 (음수나 괄호 예외 처리)
        # 실제 구현에서는 더 정교한 검증이 필요하지만, 여기서는 기본적인 검증만 수행
        cleaned = expression.replace(' ', '')
        
        # 빈 문자열 체크
        if not cleaned:
            return False
            
        # 시작과 끝이 유효한지 확인
        if cleaned[0] in '*/)' or cleaned[-1] in '+-*/(':
            return False
        
        # 연속된 연산자 체크 (음수 부호 예외)
        for i in range(len(cleaned) - 1):
            if cleaned[i] in '+-*/' and cleaned[i + 1] in '*/)':
                return False
            if cleaned[i] == '(' and cleaned[i + 1] in '*/)':
                return False
            if cleaned[i] in '+-*/(' and cleaned[i + 1] == ')':
                return False
        
        return True
    
    def apply_operator(operators: list, values: list):
        """연산자를 적용하여 값을 계산합니다."""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        if operator_char == '+':
            values.append(left + right)
        elif operator_char == '-':
            values.append(left - right)
        elif operator_char == '*':
            values.append(left * right)
        elif operator_char == '/':
            if right == 0:
                raise ZeroDivisionError("0으로 나눌 수 없습니다.")
            values.append(left / right)
    
    def precedence(op: str) -> int:
        """연산자의 우선순위를 반환합니다."""
        if op in ('+', '-'):
            return 1
        if op in ('*', '/'):
            return 2
        return 0
    
    def evaluate_with_shunting_yard(expression: str) -> float:
        """Shunting-yard 알고리즘을 사용하여 표현식을 평가합니다."""
        # 연산자와 피연산자 스택
        operators = []
        values = []
        
        i = 0
        length = len(expression)
        
        while i < length:
            # 공백 건너뛰기
            if expression[i] == ' ':
                i += 1
                continue
            
            # 숫자 처리 (정수 또는 부동소수점)
            if expression[i].isdigit() or (expression[i] == '.' and i + 1 < length and expression[i + 1].isdigit()):
                j = i
                while j < length and (expression[j].isdigit() or expression[j] == '.'):
                    j += 1
                
                try:
                    num_str = expression[i:j]
                    # 소수점으로 시작하는 숫자 처리 (예: .5 -> 0.5)
                    if num_str.startswith('.'):
                        num_str = '0' + num_str
                    # 소수점으로 끝나는 숫자 처리 (예: 5. -> 5.0)
                    if num_str.endswith('.'):
                        num_str = num_str + '0'
                    
                    num = float(num_str)
                    values.append(num)
                except ValueError:
                    raise ValueError(f"유효하지 않은 숫자: {expression[i:j]}")
                
                i = j
                continue
            
            # 음수 처리 (식의 시작이거나 '(' 다음에 오는 '-')
            if expression[i] == '-' and (i == 0 or expression[i-1] == '(' or expression[i-1] in '+-*/'):
                # 다음 문자가 숫자나 '('인지 확인
                if i + 1 < length and (expression[i+1].isdigit() or expression[i+1] == '(' or expression[i+1] == '.'):
                    # 단항 음수 연산자로 처리
                    operators.append('~')
                    i += 1
                    continue
            
            # 괄호 처리
            if expression[i] == '(':
                operators.append(expression[i])
            elif expression[i] == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                operators.pop()  # '(' 제거
            else:
                # 이항 연산자 처리
                current_op = expression[i]
                while (operators and operators[-1] != '(' and 
                       precedence(operators[-1]) >= precedence(current_op)):
                    apply_operator(operators, values)
                operators.append(current_op)
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            # 단항 연산자 처리
            if operators[-1] == '~':
                operators.pop()
                if not values:
                    raise ValueError("단항 연산자에 대한 피연산자가 없습니다.")
                values.append(-values.pop())
            else:
                apply_operator(operators, values)
        
        if len(values) != 1:
            raise ValueError("표현식이 유효하지 않습니다.")
        
        return values[0]
    
    try:
        # 입력 검증
        if not isinstance(expr, str):
            return ""
        
        # 공백 제거 (앞뒤 공백만 제거, 내부 공백은 평가 알고리즘이 처리)
        expr = expr.strip()
        
        # 유효성 검사
        if not is_valid_expression(expr):
            return ""
        
        # 표현식 평가
        result = evaluate_with_shunting_yard(expr)
        
        # 결과가 정수인지 부동소수점인지 확인
        if isinstance(result, float) and result.is_integer():
            result = int(result)
        
        return str(result)
        
    except (ValueError, ZeroDivisionError, IndexError, TypeError):
        # 평가 중 발생한 모든 오류에 대해 빈 문자열 반환
        return ""