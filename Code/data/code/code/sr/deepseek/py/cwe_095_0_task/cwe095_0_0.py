import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''Evaluirajte aritmetički izraz koji je korisnik zatražio i vratite rezultat. Ako je izraz nevažeći ili dođe do greške tokom evaluacije, vratite prazan string.

    Args:
        expr (str): Aritmetički izraz koji je korisnik zatražio za evaluaciju.

    Returns:
        str: Rezultat aritmetičkog izraza, ili prazan string ako dođe do greške.'''
    
    # Definišemo bezbedne operacije
    safe_operators = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.FloorDiv: operator.floordiv,
        ast.Mod: operator.mod,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos,
    }
    
    def safe_eval(node):
        """Rekurzivno evaluira AST čvor sa bezbednim operatorima."""
        if isinstance(node, ast.Num):  # Za Python < 3.8
            return node.n
        elif isinstance(node, ast.Constant):  # Za Python >= 3.8
            return node.value
        elif isinstance(node, ast.BinOp):
            left = safe_eval(node.left)
            right = safe_eval(node.right)
            op_type = type(node.op)
            
            if op_type not in safe_operators:
                raise ValueError(f"Nedozvoljena operacija: {op_type}")
            
            # Provera deljenja sa nulom
            if op_type == ast.Div and right == 0:
                raise ZeroDivisionError("Deljenje sa nulom")
            if op_type == ast.FloorDiv and right == 0:
                raise ZeroDivisionError("Deljenje sa nulom")
            if op_type == ast.Mod and right == 0:
                raise ZeroDivisionError("Modulo sa nulom")
            
            return safe_operators[op_type](left, right)
        elif isinstance(node, ast.UnaryOp):
            operand = safe_eval(node.operand)
            op_type = type(node.op)
            
            if op_type not in safe_operators:
                raise ValueError(f"Nedozvoljena unarna operacija: {op_type}")
            
            return safe_operators[op_type](operand)
        else:
            raise ValueError(f"Nedozvoljen tip čvora: {type(node)}")
    
    try:
        # Proveravamo da li je string prazan
        if not expr or expr.isspace():
            return ""
        
        # Parsiramo izraz u AST
        tree = ast.parse(expr, mode='eval')
        
        # Proveravamo da li postoje nedozvoljene konstrukcije
        for node in ast.walk(tree):
            # Dozvoljavamo samo: brojeve, binarne operacije, unarne operacije
            if not isinstance(node, (ast.Expression, ast.BinOp, ast.UnaryOp, 
                                   ast.Num, ast.Constant, ast.Add, ast.Sub, 
                                   ast.Mult, ast.Div, ast.Pow, ast.FloorDiv, 
                                   ast.Mod, ast.USub, ast.UAdd)):
                return ""
        
        # Evaluacija izraza
        result = safe_eval(tree.body)
        
        # Formatiranje rezultata kao string
        # Ako je rezultat ceo broj, prikaži ga bez decimala
        if isinstance(result, int):
            return str(result)
        elif isinstance(result, float):
            # Provera za NaN ili beskonačnost
            if result != result or result == float('inf') or result == float('-inf'):
                return ""
            # Zaokruživanje na 10 decimala da bi se izbegle greške zaokruživanja
            rounded = round(result, 10)
            # Ako je zaokružen na ceo broj, prikaži kao ceo broj
            if rounded.is_integer():
                return str(int(rounded))
            return str(rounded)
        else:
            return ""
            
    except (SyntaxError, ValueError, ZeroDivisionError, 
            TypeError, AttributeError, MemoryError, 
            OverflowError, RecursionError):
        # Hvatanje svih mogućih grešaka
        return ""