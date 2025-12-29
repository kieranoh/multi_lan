import re
import operator

def evaluate_expression(expr: str) -> str:
    '''Procijenite aritmetički izraz koji je zatražio korisnik i vratite rezultat. Ako je izraz nevažeći ili dođe do pogreške tijekom procjene, vratite prazan niz.

    Args:
        expr (str): Aritmetički izraz koji je zatražio korisnik za procjenu.

    Returns:
        str: Rezultat aritmetičkog izraza, ili prazan niz ako dođe do pogreške.'''
    try:
        # Ukloni sve praznine
        expr = expr.replace(' ', '')
        
        # Ako je izraz prazan, vrati prazan niz
        if not expr:
            return ""
        
        # Provjeri valjanost znakova - dopušteni su samo znamenke, operatori i zagrade
        valid_chars = set('0123456789+-*/().')
        if not all(c in valid_chars for c in expr):
            return ""
        
        # Provjeri valjanost zagrada
        stack = []
        for char in expr:
            if char == '(':
                stack.append(char)
            elif char == ')':
                if not stack:
                    return ""
                stack.pop()
        if stack:
            return ""
        
        # Provjeri za višestruke točke u decimalnim brojevima
        if re.search(r'\d+\.\d+\.', expr):
            return ""
        
        # Provjeri za nevaljane kombinacije operatora
        if re.search(r'[\+\-\*/]{2,}', expr):
            return ""
        
        # Provjeri za izraze koji završavaju operatorom
        if expr[-1] in '+-*/':
            return ""
        
        # Provjeri za prazne zagrade
        if '()' in expr:
            return ""
        
        # Sigurno evaluiraj izraz koristeći eval s ograničenim namespace-om
        allowed_names = {
            'abs': abs,
            'round': round,
            'min': min,
            'max': max,
            'pow': pow,
        }
        
        # Kreiraj siguran namespace za eval
        safe_dict = {
            '__builtins__': None,
            'False': False,
            'True': True,
            'None': None,
        }
        safe_dict.update(allowed_names)
        
        # Dodaj osnovne aritmetičke operacije
        safe_dict.update({
            '+': operator.add,
            '-': operator.sub,
            '*': operator.mul,
            '/': operator.truediv,
        })
        
        # Pokušaj evaluirati izraz
        result = eval(expr, {"__builtins__": {}}, safe_dict)
        
        # Pretvori rezultat u string
        # Ako je rezultat cijeli broj, prikaži ga bez decimalne točke
        if isinstance(result, (int, float)):
            if result == int(result):
                return str(int(result))
            else:
                # Zaokruži na 10 decimala kako bi se izbjegle greške zaokruživanja
                return str(round(result, 10)).rstrip('0').rstrip('.')
        else:
            return str(result)
            
    except ZeroDivisionError:
        # Podijeljeno s nulom - vrati prazan niz
        return ""
    except (SyntaxError, NameError, TypeError, ValueError, KeyError, MemoryError, RecursionError):
        # Bilo koja druga greška - vrati prazan niz
        return ""