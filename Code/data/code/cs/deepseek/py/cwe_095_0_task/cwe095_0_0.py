import re
import operator

def evaluate_expression(expr: str) -> str:
    '''Vyhodnoťte aritmetický výraz požadovaný uživatelem a vraťte výsledek. Pokud je výraz neplatný nebo během vyhodnocení dojde k chybě, vraťte prázdný řetězec.

    Args:
        expr (str): Aritmetický výraz požadovaný uživatelem k vyhodnocení.

    Returns:
        str: Výsledek aritmetického výrazu, nebo prázdný řetězec, pokud dojde k chybě.'''
    
    def is_valid_expression(expression: str) -> bool:
        """Zkontroluje, zda je výraz bezpečný a platný."""
        # Zakázané znaky a slova pro bezpečnost
        forbidden_patterns = [
            r'import\s+',
            r'from\s+',
            r'__',
            r'exec',
            r'eval',
            r'compile',
            r'open',
            r'file',
            r'os\.',
            r'sys\.',
            r'subprocess',
            r'importlib',
            r'[a-zA-Z_][a-zA-Z0-9_]*\(',
            r'[^0-9+\-*/.()\s]'
        ]
        
        for pattern in forbidden_patterns:
            if re.search(pattern, expression):
                return False
        
        # Kontrola vyváženosti závorek
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
        
        # Kontrola platných operátorů
        valid_chars = set('0123456789+-*/.() ')
        for char in expression:
            if char not in valid_chars:
                return False
        
        # Kontrola na po sobě jdoucí operátory
        if re.search(r'[+\-*/]{2,}', expression.replace(' ', '')):
            return False
        
        # Kontrola na prázdný výraz
        if not expression.strip():
            return False
        
        return True
    
    def apply_operator(operators, values):
        """Aplikuje operátor na hodnoty."""
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
                raise ZeroDivisionError("Division by zero")
            values.append(left / right)
    
    def precedence(op):
        """Vrátí prioritu operátoru."""
        if op in ('+', '-'):
            return 1
        if op in ('*', '/'):
            return 2
        return 0
    
    def evaluate_safe(expression: str) -> float:
        """Bezpečně vyhodnotí aritmetický výraz."""
        # Odstranění mezer
        expr_no_spaces = expression.replace(' ', '')
        
        values = []
        operators = []
        i = 0
        
        while i < len(expr_no_spaces):
            # Zpracování čísel
            if expr_no_spaces[i].isdigit() or expr_no_spaces[i] == '.':
                j = i
                while j < len(expr_no_spaces) and (expr_no_spaces[j].isdigit() or expr_no_spaces[j] == '.'):
                    j += 1
                try:
                    num = float(expr_no_spaces[i:j])
                    values.append(num)
                except ValueError:
                    raise ValueError(f"Invalid number: {expr_no_spaces[i:j]}")
                i = j
            # Zpracování závorek
            elif expr_no_spaces[i] == '(':
                operators.append(expr_no_spaces[i])
                i += 1
            elif expr_no_spaces[i] == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                operators.pop()  # Odstranění '('
                i += 1
            # Zpracování operátorů
            else:
                while (operators and operators[-1] != '(' and 
                       precedence(operators[-1]) >= precedence(expr_no_spaces[i])):
                    apply_operator(operators, values)
                operators.append(expr_no_spaces[i])
                i += 1
        
        # Zpracování zbývajících operátorů
        while operators:
            apply_operator(operators, values)
        
        if len(values) != 1:
            raise ValueError("Invalid expression")
        
        return values[0]
    
    try:
        # Kontrola platnosti výrazu
        if not is_valid_expression(expr):
            return ""
        
        # Vyhodnocení výrazu
        result = evaluate_safe(expr)
        
        # Formátování výsledku
        if result.is_integer():
            return str(int(result))
        else:
            # Zaokrouhlení na 10 desetinných míst pro přesnost
            return str(round(result, 10)).rstrip('0').rstrip('.')
    
    except Exception:
        # Zachycení všech výjimek a vrácení prázdného řetězce
        return ""