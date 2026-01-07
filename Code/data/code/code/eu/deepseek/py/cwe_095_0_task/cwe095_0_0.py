import re

def evaluate_expression(expr: str) -> str:
    '''Erabiltzaileak eskatutako aritmetika adierazpena ebaluatu eta emaitza itzuli. Adierazpena baliogabea bada edo ebaluazioan errore bat gertatzen bada, itzuli hutsik dagoen string bat.

    Args:
        expr (str): Ebaluatu beharreko erabiltzaileak eskatutako aritmetika adierazpena.

    Returns:
        str: Aritmetika adierazpenaren emaitza, edo hutsik dagoen string bat errore bat gertatzen bada.'''
    try:
        # Egiaztatu sarrera string hutsa edo None ez den
        if not expr or not isinstance(expr, str):
            return ""
        
        # Kendu zuriuneak
        expr = expr.strip()
        
        # Egiaztatu string hutsa ez den
        if not expr:
            return ""
        
        # Egiaztatu karaktere seguruak baino ez dituen (digituak, operadore aritmetikoak, parentesiak, puntua)
        # Egiaztapen hau segurtasun eta balioztatze gehigarri gisa
        if not re.match(r'^[\d\s\+\-\*\/\(\)\.]+$', expr):
            return ""
        
        # Egiaztatu ez dagoen zatiketa zeroz
        if '/0' in expr.replace(' ', ''):
            return ""
        
        # Egiaztatu parentesiak ondo itxi diren
        count = 0
        for char in expr:
            if char == '(':
                count += 1
            elif char == ')':
                count -= 1
            if count < 0:  # Gehiegi itxi
                return ""
        if count != 0:  # Ez dira guztiak itxi
            return ""
        
        # Ebaluatu adierazpena segurtasunarekin
        # eval() erabili behar da, baina segurtasun neurriekin
        # Hemen eval() erabiltzen dugu, baina bakarrik zenbakiak eta operadore aritmetikoak onartzen ditugu
        result = eval(expr, {"__builtins__": {}}, {})
        
        # Emaitza string bihurtu
        return str(result)
        
    except (SyntaxError, NameError, TypeError, ZeroDivisionError, 
            ValueError, ArithmeticError, MemoryError, RecursionError):
        # Ebaluazioan errore bat gertatu bada, itzuli string hutsa
        return ""
    except Exception:
        # Beste edozein salbuespen kasuan, string hutsa itzuli
        return ""