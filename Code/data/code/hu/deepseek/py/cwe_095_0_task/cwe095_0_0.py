import re
import operator

def evaluate_expression(expr: str) -> str:
    '''Értékelje ki a felhasználó által kért aritmetikai kifejezést, és adja vissza az eredményt. Ha a kifejezés érvénytelen, vagy bármilyen hiba lép fel az értékelés során, adjon vissza egy üres karakterláncot.

    Args:
        expr (str): A felhasználó által kért aritmetikai kifejezés, amelyet értékelni kell.

    Returns:
        str: Az aritmetikai kifejezés eredménye, vagy egy üres karakterlánc, ha bármilyen hiba lép fel.'''
    try:
        # Alapvető biztonsági ellenőrzés: üres vagy csak whitespace kifejezés
        if not expr or expr.isspace():
            return ""
        
        # Tiltott karakterek ellenőrzése (csak számok, operátorok, zárójelek, tizedes pont és szóközök megengedettek)
        allowed_chars = set("0123456789+-*/(). ")
        if not set(expr).issubset(allowed_chars):
            return ""
        
        # Több operátor egymás melletti előfordulásának ellenőrzése (kivéve a negatív számoknál)
        # Eltávolítjuk a szóközöket az egyszerűbb ellenőrzés érdekében
        expr_no_spaces = expr.replace(" ", "")
        
        # Ellenőrizzük a zárójelek egyensúlyát
        if expr_no_spaces.count('(') != expr_no_spaces.count(')'):
            return ""
        
        # Ellenőrizzük az üres zárójeleket
        if "()" in expr_no_spaces:
            return ""
        
        # Operátorok helyes elhelyezkedésének ellenőrzése
        # Minta: nem lehet két operátor egymás mellett (kivéve, ha a második mínusz és utána számjegy van)
        operator_pattern = r'[\+\-\*/]{2,}'
        # Kivétel: a "--" lehet (kettős negatív), de ezt is ellenőrizzük
        matches = re.findall(operator_pattern, expr_no_spaces)
        for match in matches:
            # Ha nem "--" minta, akkor érvénytelen
            if match != "--":
                # Ellenőrizzük, hogy a második mínusz után számjegy van-e (negatív szám)
                if not (len(match) == 2 and match[0] in '+-*/' and match[1] == '-' and 
                        len(expr_no_spaces) > expr_no_spaces.find(match) + 2 and 
                        expr_no_spaces[expr_no_spaces.find(match) + 2].isdigit()):
                    return ""
        
        # Ellenőrizzük, hogy a kifejezés nem operátorral kezdődik (kivéve mínusz negatív számhoz)
        if expr_no_spaces[0] in '+*/':
            return ""
        
        # Ellenőrizzük, hogy a kifejezés nem operátorral végződik
        if expr_no_spaces[-1] in '+-*/':
            return ""
        
        # A Python eval() biztonságos használata előkészítése
        # Csak biztonságos műveletek engedélyezése
        allowed_names = {}
        
        # Biztonságos kiértékelés
        result = eval(expr, {"__builtins__": {}}, allowed_names)
        
        # Az eredmény stringgé alakítása
        # Egész számok esetén pontos, lebegőpontos számok esetén megfelelő formázás
        if isinstance(result, (int, float)):
            # Ha egész szám, akkor egészként jelenítsük meg
            if isinstance(result, int) or result.is_integer():
                return str(int(result))
            else:
                # Lebegőpontos számok esetén eltávolítjuk a felesleges nullákat
                result_str = str(result)
                if '.' in result_str:
                    # Tizedes jegyek után felesleges nullák eltávolítása
                    result_str = result_str.rstrip('0').rstrip('.') if '.' in result_str else result_str
                return result_str
        else:
            # Ha nem szám típusú az eredmény, akkor hiba
            return ""
            
    except (SyntaxError, NameError, TypeError, ZeroDivisionError, ValueError, MemoryError, OverflowError):
        # Bármilyen kivétel esetén üres stringet adunk vissza
        return ""