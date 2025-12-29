import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''Avaluar una expressió aritmètica sol·licitada per l'usuari i retornar el resultat. Si l'expressió és invàlida o es produeix un error durant l'avaluació, retornar una cadena buida.

    Args:
        expr (str): L'expressió aritmètica sol·licitada per l'usuari a avaluar.

    Returns:
        str: El resultat de l'expressió aritmètica, o una cadena buida si es produeix algun error.'''
    
    # Diccionari d'operadors permesos per a l'avaluació segura
    ALLOWED_OPERATORS = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos
    }
    
    class SafeEvaluator(ast.NodeVisitor):
        """Visitor per avaluar expressions aritmètiques de manera segura."""
        
        def visit_BinOp(self, node):
            left = self.visit(node.left)
            right = self.visit(node.right)
            
            # Obtenir l'operador i verificar que estigui permès
            op_type = type(node.op)
            if op_type not in ALLOWED_OPERATORS:
                raise ValueError(f"Operador no permès: {op_type}")
            
            # Realitzar l'operació
            try:
                return ALLOWED_OPERATORS[op_type](left, right)
            except ZeroDivisionError:
                raise ValueError("Divisió per zero")
            except Exception:
                raise ValueError("Error en l'operació")
        
        def visit_UnaryOp(self, node):
            operand = self.visit(node.operand)
            
            # Obtenir l'operador i verificar que estigui permès
            op_type = type(node.op)
            if op_type not in ALLOWED_OPERATORS:
                raise ValueError(f"Operador unari no permès: {op_type}")
            
            # Realitzar l'operació unària
            try:
                return ALLOWED_OPERATORS[op_type](operand)
            except Exception:
                raise ValueError("Error en l'operació unària")
        
        def visit_Num(self, node):
            return node.n
        
        def visit_Constant(self, node):
            # Per a Python 3.8+, Constant reemplaça Num, Str, Bytes, etc.
            if isinstance(node.value, (int, float)):
                return node.value
            raise ValueError("Només es permeten constants numèriques")
        
        def generic_visit(self, node):
            # Bloquejar qualsevol altre tipus de node
            raise ValueError(f"Tipus de node no permès: {type(node).__name__}")
    
    try:
        # Verificar que l'expressió no estigui buida
        expr = expr.strip()
        if not expr:
            return ""
        
        # Parsejar l'expressió
        tree = ast.parse(expr, mode='eval')
        
        # Crear l'avaluador segur
        evaluator = SafeEvaluator()
        
        # Avaluar l'expressió
        result = evaluator.visit(tree.body)
        
        # Convertir el resultat a cadena
        # Si és un enter, mostrar-lo sense decimals
        if isinstance(result, int):
            return str(result)
        # Si és un float, mostrar-lo amb un màxim de 10 decimals
        elif isinstance(result, float):
            # Formatejar per eliminar zeros innecessaris
            formatted = f"{result:.10f}"
            # Eliminar zeros decimals innecessaris
            if '.' in formatted:
                formatted = formatted.rstrip('0').rstrip('.')
            return formatted
        else:
            # Per a qualsevol altre tipus, convertir a cadena
            return str(result)
            
    except (SyntaxError, ValueError, TypeError, ZeroDivisionError, MemoryError, 
            OverflowError, AttributeError, NameError, KeyError, IndexError) as e:
        # Capturar qualsevol error i retornar cadena buida
        return ""
    except Exception:
        # Capturar qualsevol altre excepció inesperada
        return ""