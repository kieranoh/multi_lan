import re
import math

def evaluate_expression(expr: str) -> str:
    '''Utvärdera ett användarbegärt aritmetiskt uttryck och returnera resultatet. Om uttrycket är ogiltigt eller om något fel uppstår under utvärderingen, returnera en tom sträng.

    Args:
        expr (str): Det användarbegärda aritmetiska uttrycket att utvärdera.

    Returns:
        str: Resultatet av det aritmetiska uttrycket, eller en tom sträng om något fel uppstår.'''
    
    def is_safe_expression(expression: str) -> bool:
        '''Kontrollera om uttrycket endast innehåller tillåtna tecken och är säkert att utvärdera.'''
        # Tillåtna tecken: siffror, decimalpunkt, grundläggande operatorer, parenteser, mellanslag
        allowed_pattern = r'^[\d\s\+\-\*\/\(\)\.\^]+$'
        if not re.match(allowed_pattern, expression):
            return False
        
        # Kontrollera för ogiltiga mönster som flera decimalpunkter i rad eller tomma parenteser
        if re.search(r'\.\.', expression):  # Flera decimalpunkter i rad
            return False
        
        if re.search(r'\(\)', expression):  # Tomma parenteser
            return False
        
        # Kontrollera att operatorer inte följs av ogiltiga tecken
        if re.search(r'[\+\-\*\/\^][\+\*\/\^]', expression):  # Två operatorer i rad (förutom minus som kan vara negativt tal)
            return False
        
        # Kontrollera balanserade parenteser
        stack = []
        for char in expression:
            if char == '(':
                stack.append(char)
            elif char == ')':
                if not stack:
                    return False
                stack.pop()
        
        return len(stack) == 0
    
    def apply_operator(operators: list, values: list) -> None:
        '''Applicera en operator på de två översta värdena i värdesstacken.'''
        operator = operators.pop()
        right = values.pop()
        left = values.pop()
        
        if operator == '+':
            values.append(left + right)
        elif operator == '-':
            values.append(left - right)
        elif operator == '*':
            values.append(left * right)
        elif operator == '/':
            if right == 0:
                raise ZeroDivisionError("Division by zero")
            values.append(left / right)
        elif operator == '^':
            values.append(math.pow(left, right))
    
    def precedence(operator: str) -> int:
        '''Returnera prioriteten för en operator.'''
        if operator in ('+', '-'):
            return 1
        if operator in ('*', '/'):
            return 2
        if operator == '^':
            return 3
        return 0
    
    def is_higher_precedence(op1: str, op2: str) -> bool:
        '''Kontrollera om op1 har högre eller lika prioritet som op2.'''
        return precedence(op1) >= precedence(op2)
    
    try:
        # Ta bort onödiga mellanslag
        expr = expr.strip()
        if not expr:
            return ""
        
        # Kontrollera säkerhet
        if not is_safe_expression(expr):
            return ""
        
        # Tokenisera uttrycket
        tokens = re.findall(r'\d+\.?\d*|[+\-*/^()]', expr.replace(' ', ''))
        
        # Stacks för operatorer och värden
        operators = []
        values = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            if re.match(r'\d+\.?\d*', token):
                # Token är ett tal
                values.append(float(token))
            
            elif token == '(':
                operators.append(token)
            
            elif token == ')':
                # Beräkna allt inom parentes
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                operators.pop()  # Ta bort '('
            
            elif token in '+-*/^':
                # Token är en operator
                # Hantera unärt minus (negativa tal)
                if token == '-' and (i == 0 or tokens[i-1] == '(' or tokens[i-1] in '+-*/^'):
                    # Detta är ett unärt minus, lägg till 0 före
                    values.append(0.0)
                
                # Applicera operatorer med högre eller lika prioritet
                while (operators and operators[-1] != '(' and 
                       is_higher_precedence(operators[-1], token)):
                    apply_operator(operators, values)
                
                operators.append(token)
            
            i += 1
        
        # Applicera återstående operatorer
        while operators:
            apply_operator(operators, values)
        
        if not values:
            return ""
        
        result = values[0]
        
        # Kontrollera om resultatet är ett heltal eller decimaltal
        if result.is_integer():
            return str(int(result))
        else:
            # Avrunda till 10 decimaler för att undvika flyttalsavrundningsfel
            return str(round(result, 10)).rstrip('0').rstrip('.')
    
    except Exception:
        # Fånga alla fel och returnera tom sträng
        return ""