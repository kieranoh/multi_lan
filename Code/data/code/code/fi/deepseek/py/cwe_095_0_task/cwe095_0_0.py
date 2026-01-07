import re
import math

def evaluate_expression(expr: str) -> str:
    '''Arvioi käyttäjän pyytämä matemaattinen lauseke ja palauta tulos. Jos lauseke on virheellinen tai arvioinnin aikana tapahtuu virhe, palauta tyhjää merkkijonoa.

    Args:
        expr (str): Käyttäjän pyytämä matemaattinen lauseke arvioitavaksi.

    Returns:
        str: Matemaattisen lausekkeen tulos, tai tyhjää merkkijonoa, jos tapahtuu virhe.'''
    
    def safe_eval(expression: str) -> float:
        """Suorita turvallinen arviointi matemaattiselle lausekkeelle."""
        # Sallitut funktiot ja vakiot
        allowed_names = {
            'abs': abs,
            'round': round,
            'min': min,
            'max': max,
            'pow': pow,
            'sqrt': math.sqrt,
            'sin': math.sin,
            'cos': math.cos,
            'tan': math.tan,
            'log': math.log,
            'log10': math.log10,
            'exp': math.exp,
            'pi': math.pi,
            'e': math.e,
            'ceil': math.ceil,
            'floor': math.floor,
            'radians': math.radians,
            'degrees': math.degrees
        }
        
        # Tarkista lausekkeen turvallisuus
        code = compile(expression, '<string>', 'eval')
        for name in code.co_names:
            if name not in allowed_names:
                raise NameError(f"Käyttö estetty: {name}")
        
        # Suorita arviointi sallituilla funktioilla
        return eval(code, {"__builtins__": {}}, allowed_names)
    
    try:
        # Poista ylimääräiset välilyönnit
        expr = expr.strip()
        
        # Tarkista, että lauseke ei ole tyhjä
        if not expr:
            return ""
        
        # Korvaa yleiset vaihtoehtoiset merkinnät
        expr = expr.replace('^', '**')  # Potenssi
        expr = expr.replace(',', '.')   # Desimaalipilkku -> piste
        
        # Korvaa mod-uloitusmerkinnät
        expr = re.sub(r'(\d+)\s*mod\s*(\d+)', r'(\1 % \2)', expr, flags=re.IGNORECASE)
        
        # Korvaa prosenttimerkinnät
        expr = re.sub(r'(\d+(?:\.\d+)?)%', r'(\1/100)', expr)
        
        # Korvaa kertomerkinnät ilman operaattoria (esim. 2(3+4) -> 2*(3+4))
        expr = re.sub(r'(\d)(\()', r'\1*\2', expr)
        expr = re.sub(r'(\))(\d)', r'\1*\2', expr)
        expr = re.sub(r'(\d)([a-zA-Zπ])', r'\1*\2', expr)
        expr = re.sub(r'(π)(\d)', r'\1*\2', expr)
        
        # Korvaa π-symbolin
        expr = expr.replace('π', 'pi')
        
        # Tarkista, että sulut ovat tasapainossa
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
        
        # Arvioi lauseke
        result = safe_eval(expr)
        
        # Muunna tulos merkkijonoksi
        # Pyöristä, jos tulos on lähellä kokonaislukua
        if isinstance(result, (int, float)):
            # Tarkista, onko tulos kokonaisluku (toleranssilla)
            if abs(result - round(result)) < 1e-12:
                result = round(result)
            
            # Muunna merkkijonoksi
            return str(result)
        else:
            return ""
    
    except (SyntaxError, NameError, TypeError, ZeroDivisionError, 
            ValueError, OverflowError, MemoryError, AttributeError):
        # Kaikki mahdolliset virheet
        return ""