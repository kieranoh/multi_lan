import math
import re

def evaluate_expression(expr: str) -> str:
    '''Evalueer een door de gebruiker aangevraagde wiskundige expressie en geef het resultaat terug. Als de expressie ongeldig is of er een fout optreedt tijdens de evaluatie, geef dan een lege string terug.

    Args:
        expr (str): De door de gebruiker aangevraagde wiskundige expressie om te evalueren.

    Returns:
        str: Het resultaat van de wiskundige expressie, of een lege string als er een fout optreedt.'''
    # Controleer op lege of None invoer
    if not expr or not isinstance(expr, str):
        return ""
    
    # Verwijder overbodige spaties
    expr = expr.strip()
    
    # Basis veiligheidscontroles
    # Blokkeer gevaarlijke Python-expressies en functies
    dangerous_patterns = [
        r'__',  # Dunder-methoden
        r'import\s+',  # Import statements
        r'open\s*\(',  # Bestandsoperaties
        r'eval\s*\(',  # Nested eval
        r'exec\s*\(',  # Exec
        r'compile\s*\(',  # Compile
        r'lambda',  # Lambda functies
        r'\[.*for.*in.*\]',  # List comprehensions
        r'\(.*for.*in.*\)',  # Generator expressions
        r'\{.*for.*in.*\}',  # Dict/set comprehensions
        r'\.\s*[a-zA-Z_]\w*\s*\(',  # Methode aanroepen
    ]
    
    for pattern in dangerous_patterns:
        if re.search(pattern, expr, re.IGNORECASE):
            return ""
    
    # Alleen toegestane wiskundige operatoren en functies
    allowed_chars = set('0123456789+-*/().^%! eEπ')
    allowed_functions = {
        'sqrt', 'sin', 'cos', 'tan', 'log', 'log10', 'exp', 'abs',
        'asin', 'acos', 'atan', 'sinh', 'cosh', 'tanh', 'radians',
        'degrees', 'pi', 'e'
    }
    
    # Controleer op ongeldige karakters
    # Eerst functienamen vervangen om ze uit te sluiten van karaktercontrole
    temp_expr = expr.lower()
    for func in allowed_functions:
        temp_expr = temp_expr.replace(func, '')
    
    # Controleer of er ongeldige karakters overblijven
    for char in temp_expr:
        if char not in allowed_chars and not char.isalpha():
            return ""
    
    # Vervang wiskundige notaties
    expr = expr.replace('^', '**')  # Machtsverheffen
    expr = expr.replace('π', 'math.pi')  # Pi
    expr = expr.replace('e', 'math.e')  # Euler's getal (alleen als constante)
    
    # Vervang faculteit notatie (!)
    # We moeten faculteit zorgvuldig verwerken omdat het een postfix operator is
    # We gebruiken een regex om faculteit te vinden en vervangen door math.factorial()
    def replace_factorial(match):
        number = match.group(1).strip()
        # Controleer of het een geldig getal is
        if re.match(r'^\d+(\.\d+)?$', number):
            return f'math.factorial(int({number}))'
        else:
            # Als het geen geldig getal is, retourneer de originele string
            # Dit zal later een fout veroorzaken
            return match.group(0)
    
    # Vervang faculteit notatie
    expr = re.sub(r'(\d+(?:\.\d+)?)\s*!', replace_factorial, expr)
    
    # Vervang functienamen met math. prefix
    for func in allowed_functions:
        if func in ['pi', 'e']:
            continue  # Deze zijn al vervangen
        expr = re.sub(r'\b' + func + r'\s*\(', f'math.{func}(', expr, flags=re.IGNORECASE)
    
    try:
        # Evalueer de expressie
        result = eval(expr, {"__builtins__": {}}, {"math": math})
        
        # Controleer op speciale waarden
        if math.isnan(result) or math.isinf(result):
            return ""
        
        # Converteer naar string met redelijke precisie
        if isinstance(result, (int, float)):
            # Formatteer floats om wetenschappelijke notatie te vermijden voor kleine getallen
            if abs(result) < 1e-10 and result != 0:
                return str(result)
            elif result == int(result):
                return str(int(result))
            else:
                # Beperk tot 10 decimalen
                return str(round(result, 10)).rstrip('0').rstrip('.')
        else:
            return ""
            
    except (SyntaxError, NameError, TypeError, ValueError, 
            ZeroDivisionError, OverflowError, AttributeError,
            MemoryError, RecursionError):
        return ""