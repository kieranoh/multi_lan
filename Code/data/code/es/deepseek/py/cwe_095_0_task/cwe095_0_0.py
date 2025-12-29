import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''Evalúa una expresión aritmética solicitada por el usuario y devuelve el resultado. Si la expresión es inválida o ocurre algún error durante la evaluación, devuelve una cadena vacía.

    Args:
        expr (str): La expresión aritmética solicitada por el usuario para evaluar.

    Returns:
        str: El resultado de la expresión aritmética, o una cadena vacía si ocurre algún error.'''
    
    # Diccionario de operadores seguros permitidos
    safe_operators = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos
    }
    
    def safe_eval(node):
        """Evalúa de forma segura un nodo AST."""
        if isinstance(node, ast.Num):  # Para Python 3.7 y anteriores
            return node.n
        elif isinstance(node, ast.Constant):  # Para Python 3.8+
            return node.value
        elif isinstance(node, ast.BinOp):
            try:
                left = safe_eval(node.left)
                right = safe_eval(node.right)
                op_type = type(node.op)
                if op_type in safe_operators:
                    # Manejar división por cero
                    if op_type is ast.Div and right == 0:
                        raise ZeroDivisionError("División por cero")
                    return safe_operators[op_type](left, right)
                else:
                    raise ValueError(f"Operador no permitido: {op_type}")
            except (ZeroDivisionError, ValueError, TypeError) as e:
                raise e
        elif isinstance(node, ast.UnaryOp):
            try:
                operand = safe_eval(node.operand)
                op_type = type(node.op)
                if op_type in safe_operators:
                    return safe_operators[op_type](operand)
                else:
                    raise ValueError(f"Operador unario no permitido: {op_type}")
            except (ValueError, TypeError) as e:
                raise e
        else:
            raise ValueError(f"Nodo AST no permitido: {type(node)}")
    
    try:
        # Verificar si la expresión está vacía o solo contiene espacios
        if not expr or expr.isspace():
            return ""
        
        # Limpiar la expresión eliminando espacios en blanco
        expr_clean = expr.strip()
        
        # Parsear la expresión en un AST
        tree = ast.parse(expr_clean, mode='eval')
        
        # Evaluar de forma segura el AST
        result = safe_eval(tree.body)
        
        # Convertir el resultado a string
        # Si es un número entero, mostrarlo sin decimales
        if isinstance(result, int) or (isinstance(result, float) and result.is_integer()):
            return str(int(result))
        elif isinstance(result, float):
            # Formatear para evitar notación científica y mostrar con precisión razonable
            return format(result, 'f').rstrip('0').rstrip('.')
        else:
            return str(result)
            
    except (SyntaxError, ValueError, TypeError, ZeroDivisionError, 
            MemoryError, RecursionError, AttributeError, 
            KeyError, IndexError, OverflowError):
        # Capturar cualquier error durante la evaluación
        return ""