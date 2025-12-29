import re
import operator

def evaluate_expression(expr: str) -> str:
    '''Bewerte einen vom Benutzer angeforderten arithmetischen Ausdruck und gib das Ergebnis zurück. Wenn der Ausdruck ungültig ist oder während der Auswertung ein Fehler auftritt, gib einen leeren String zurück.

    Args:
        expr (str): Der vom Benutzer angeforderte arithmetische Ausdruck zur Auswertung.

    Returns:
        str: Das Ergebnis des arithmetischen Ausdrucks oder ein leerer String, wenn ein Fehler auftritt.'''
    
    def is_valid_expression(expression: str) -> bool:
        """Prüft, ob der Ausdruck nur erlaubte Zeichen enthält."""
        allowed_chars = set('0123456789+-*/(). ')
        return all(char in allowed_chars for char in expression)
    
    def has_balanced_parentheses(expression: str) -> bool:
        """Prüft, ob die Klammern im Ausdruck korrekt ausgeglichen sind."""
        count = 0
        for char in expression:
            if char == '(':
                count += 1
            elif char == ')':
                count -= 1
                if count < 0:
                    return False
        return count == 0
    
    def tokenize(expression: str):
        """Zerlegt den Ausdruck in Tokens."""
        tokens = []
        i = 0
        while i < len(expression):
            if expression[i].isdigit():
                j = i
                while j < len(expression) and (expression[j].isdigit() or expression[j] == '.'):
                    j += 1
                tokens.append(expression[i:j])
                i = j
            elif expression[i] in '+-*/()':
                tokens.append(expression[i])
                i += 1
            elif expression[i] == ' ':
                i += 1
            else:
                return None
        return tokens
    
    def shunting_yard(tokens):
        """Wendet den Shunting-Yard-Algorithmus an, um Infix in Postfix umzuwandeln."""
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
        output = []
        operators = []
        
        for token in tokens:
            if re.match(r'^\d+(\.\d+)?$', token):
                output.append(token)
            elif token in precedence:
                while (operators and operators[-1] != '(' and 
                       precedence[operators[-1]] >= precedence[token]):
                    output.append(operators.pop())
                operators.append(token)
            elif token == '(':
                operators.append(token)
            elif token == ')':
                while operators and operators[-1] != '(':
                    output.append(operators.pop())
                if not operators:
                    return None
                operators.pop()
        
        while operators:
            if operators[-1] == '(':
                return None
            output.append(operators.pop())
        
        return output
    
    def evaluate_postfix(postfix):
        """Bewertet einen Postfix-Ausdruck."""
        stack = []
        ops = {
            '+': operator.add,
            '-': operator.sub,
            '*': operator.mul,
            '/': operator.truediv
        }
        
        for token in postfix:
            if re.match(r'^\d+(\.\d+)?$', token):
                stack.append(float(token))
            elif token in ops:
                if len(stack) < 2:
                    return None
                b = stack.pop()
                a = stack.pop()
                try:
                    if token == '/' and b == 0:
                        return None
                    result = ops[token](a, b)
                    stack.append(result)
                except:
                    return None
            else:
                return None
        
        if len(stack) != 1:
            return None
        
        return stack[0]
    
    try:
        # Leeren String oder nur Whitespace behandeln
        if not expr or expr.isspace():
            return ""
        
        # Ungültige Zeichen prüfen
        if not is_valid_expression(expr):
            return ""
        
        # Ausgeglichene Klammern prüfen
        if not has_balanced_parentheses(expr):
            return ""
        
        # Tokenisierung
        tokens = tokenize(expr)
        if tokens is None:
            return ""
        
        # Infix zu Postfix konvertieren
        postfix = shunting_yard(tokens)
        if postfix is None:
            return ""
        
        # Postfix auswerten
        result = evaluate_postfix(postfix)
        if result is None:
            return ""
        
        # Ergebnis formatieren (Ganzzahl ohne .0, sonst mit angemessener Genauigkeit)
        if isinstance(result, float) and result.is_integer():
            return str(int(result))
        else:
            # Auf 10 Dezimalstellen runden, um Gleitkommafehler zu minimieren
            result = round(result, 10)
            # Überflüssige Nullen entfernen
            result_str = ('{:.10f}'.format(result)).rstrip('0').rstrip('.')
            return result_str
            
    except Exception:
        return ""