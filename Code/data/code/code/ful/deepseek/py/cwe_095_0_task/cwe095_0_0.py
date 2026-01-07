import re
import operator

def evaluate_expression(expr: str) -> str:
    '''사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

    Args:
        expr (str): 평가할 사용자 요청 산술 표현식입니다.

    Returns:
        str: 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.'''
    
    # 입력 검증: 빈 문자열이나 None인 경우 빈 문자열 반환
    if not expr or not isinstance(expr, str):
        return ""
    
    # 표현식 정리: 공백 제거
    expr = expr.strip()
    if not expr:
        return ""
    
    # 허용된 문자 패턴: 숫자, 기본 연산자(+, -, *, /), 괄호, 공백, 소수점
    # 보안을 위해 알파벳이나 특수 문자를 제한
    allowed_pattern = re.compile(r'^[\d+\-*/().\s]+$')
    if not allowed_pattern.match(expr):
        return ""
    
    # 연산자 우선순위 및 함수 매핑
    ops = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv
    }
    
    # 중위 표현식을 후위 표현식으로 변환 (Shunting-yard 알고리즘)
    def infix_to_postfix(expression: str) -> list:
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
        output = []
        stack = []
        i = 0
        length = len(expression)
        
        while i < length:
            ch = expression[i]
            
            # 공백 건너뛰기
            if ch == ' ':
                i += 1
                continue
            
            # 숫자나 소수점 처리 (다중 자리 숫자 및 부동 소수점)
            if ch.isdigit() or ch == '.':
                num = ''
                while i < length and (expression[i].isdigit() or expression[i] == '.'):
                    num += expression[i]
                    i += 1
                # 유효한 숫자인지 확인
                try:
                    # 소수점이 여러 개 있는지 확인
                    if num.count('.') > 1:
                        raise ValueError
                    output.append(float(num) if '.' in num else int(num))
                except ValueError:
                    return []  # 유효하지 않은 숫자 형식
                continue
            
            # 왼쪽 괄호 처리
            elif ch == '(':
                stack.append(ch)
            
            # 오른쪽 괄호 처리
            elif ch == ')':
                while stack and stack[-1] != '(':
                    output.append(stack.pop())
                if not stack:  # 짝이 맞지 않는 괄호
                    return []
                stack.pop()  # '(' 제거
            
            # 연산자 처리
            elif ch in precedence:
                while (stack and stack[-1] != '(' and 
                       precedence.get(stack[-1], 0) >= precedence[ch]):
                    output.append(stack.pop())
                stack.append(ch)
            
            else:
                # 허용되지 않은 문자
                return []
            
            i += 1
        
        # 스택에 남은 연산자 처리
        while stack:
            op = stack.pop()
            if op == '(':  # 짝이 맞지 않는 괄호
                return []
            output.append(op)
        
        return output
    
    # 후위 표현식 평가
    def evaluate_postfix(postfix: list) -> float:
        stack = []
        
        for token in postfix:
            if isinstance(token, (int, float)):
                stack.append(token)
            else:  # 연산자
                if len(stack) < 2:
                    raise ValueError("연산자에 대한 피연산자 부족")
                b = stack.pop()
                a = stack.pop()
                
                # 0으로 나누기 방지
                if token == '/' and b == 0:
                    raise ZeroDivisionError("0으로 나눌 수 없습니다")
                
                result = ops[token](a, b)
                stack.append(result)
        
        if len(stack) != 1:
            raise ValueError("유효하지 않은 표현식")
        
        return stack[0]
    
    try:
        # 후위 표현식으로 변환
        postfix = infix_to_postfix(expr)
        if not postfix:
            return ""
        
        # 표현식 평가
        result = evaluate_postfix(postfix)
        
        # 결과를 문자열로 변환 (정수인 경우 소수점 없이, 부동 소수점인 경우 적절히)
        if isinstance(result, int) or result.is_integer():
            return str(int(result))
        else:
            # 부동 소수점 정밀도 제한 (필요시 조정)
            return str(round(result, 10)).rstrip('0').rstrip('.')
    
    except (ValueError, ZeroDivisionError, KeyError, IndexError, TypeError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""