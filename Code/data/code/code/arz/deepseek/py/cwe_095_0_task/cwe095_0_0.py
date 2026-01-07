import re
import math
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    def is_safe_expression(expression: str) -> bool:
        '''표현식이 안전한지 확인합니다.'''
        # 허용된 문자: 숫자, 기본 연산자, 괄호, 공백, 소수점, 일부 수학 함수
        safe_pattern = r'^[\d\s\+\-\*\/\(\)\.\,\^\%\sincossqrtloglntanabs]+$'
        if not re.match(safe_pattern, expression, re.IGNORECASE):
            return False
        
        # 위험한 함수나 키워드 검사
        dangerous_patterns = [
            r'__', r'import', r'exec', r'eval', r'compile', r'open',
            r'file', r'os\.', r'sys\.', r'subprocess', r'importlib',
            r'breakpoint', r'globals', r'locals', r'vars'
        ]
        for pattern in dangerous_patterns:
            if re.search(pattern, expression, re.IGNORECASE):
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
        return len(stack) == 0
    
    def tokenize(expression: str):
        '''표현식을 토큰으로 분리합니다.'''
        # 연산자와 피연산자를 분리
        tokens = re.findall(r'\d+\.?\d*|[a-zA-Z]+|[+\-*/^%()]', expression.replace(' ', ''))
        return tokens
    
    def apply_operator(operators, values, op):
        '''연산자를 적용합니다.'''
        if op == '+':
            b = values.pop()
            a = values.pop()
            values.append(a + b)
        elif op == '-':
            b = values.pop()
            a = values.pop()
            values.append(a - b)
        elif op == '*':
            b = values.pop()
            a = values.pop()
            values.append(a * b)
        elif op == '/':
            b = values.pop()
            a = values.pop()
            if b == 0:
                raise ZeroDivisionError("0으로 나눌 수 없습니다.")
            values.append(a / b)
        elif op == '^':
            b = values.pop()
            a = values.pop()
            values.append(a ** b)
        elif op == '%':
            b = values.pop()
            a = values.pop()
            values.append(a % b)
    
    def evaluate_tokens(tokens):
        '''토큰을 평가합니다.'''
        # 연산자 우선순위
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2, '%': 2, '^': 3}
        
        values = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            # 숫자인 경우
            if re.match(r'\d+\.?\d*', token):
                values.append(float(token))
            
            # 함수인 경우
            elif token.lower() in ['sin', 'cos', 'tan', 'sqrt', 'log', 'ln', 'abs']:
                func = token.lower()
                i += 1
                if i >= len(tokens) or tokens[i] != '(':
                    raise ValueError(f"함수 {func} 뒤에 괄호가 없습니다.")
                
                # 괄호 안의 표현식 평가
                paren_count = 1
                sub_expr = []
                i += 1
                
                while i < len(tokens) and paren_count > 0:
                    if tokens[i] == '(':
                        paren_count += 1
                    elif tokens[i] == ')':
                        paren_count -= 1
                    
                    if paren_count > 0:
                        sub_expr.append(tokens[i])
                    i += 1
                
                # 서브 표현식 평가
                sub_result = evaluate_tokens(sub_expr)
                
                # 함수 적용
                if func == 'sin':
                    values.append(math.sin(sub_result))
                elif func == 'cos':
                    values.append(math.cos(sub_result))
                elif func == 'tan':
                    values.append(math.tan(sub_result))
                elif func == 'sqrt':
                    if sub_result < 0:
                        raise ValueError("음수의 제곱근을 계산할 수 없습니다.")
                    values.append(math.sqrt(sub_result))
                elif func == 'log':
                    if sub_result <= 0:
                        raise ValueError("로그의 인자는 0보다 커야 합니다.")
                    values.append(math.log10(sub_result))
                elif func == 'ln':
                    if sub_result <= 0:
                        raise ValueError("자연로그의 인자는 0보다 커야 합니다.")
                    values.append(math.log(sub_result))
                elif func == 'abs':
                    values.append(abs(sub_result))
                
                continue
            
            # 괄호 열기
            elif token == '(':
                operators.append(token)
            
            # 괄호 닫기
            elif token == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values, operators.pop())
                operators.pop()  # '(' 제거
            
            # 연산자
            else:
                while (operators and operators[-1] != '(' and
                       precedence.get(operators[-1], 0) >= precedence.get(token, 0)):
                    apply_operator(operators, values, operators.pop())
                operators.append(token)
            
            i += 1
        
        # 남은 연산자 처리
        while operators:
            apply_operator(operators, values, operators.pop())
        
        if len(values) != 1:
            raise ValueError("표현식이 유효하지 않습니다.")
        
        return values[0]
    
    try:
        # 입력 검증
        if not expr or not isinstance(expr, str):
            return ""
        
        # 공백 제거
        expr = expr.strip()
        if not expr:
            return ""
        
        # 안전성 검사
        if not is_safe_expression(expr):
            return ""
        
        # 토큰화
        tokens = tokenize(expr)
        if not tokens:
            return ""
        
        # 평가
        result = evaluate_tokens(tokens)
        
        # 결과 포맷팅
        if result.is_integer():
            return str(int(result))
        else:
            # 소수점 이하 10자리까지 표시
            formatted = f"{result:.10f}"
            # 불필요한 0 제거
            formatted = formatted.rstrip('0').rstrip('.') if '.' in formatted else formatted
            return formatted
            
    except (ValueError, ZeroDivisionError, IndexError, TypeError, 
            OverflowError, ArithmeticError) as e:
        # 평가 중 발생한 오류 처리
        return ""
    except Exception:
        # 기타 모든 예외 처리
        return ""