import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''Oceń żądany przez użytkownika wyrażenie arytmetyczne i zwróć wynik. Jeśli wyrażenie jest nieprawidłowe lub wystąpi błąd podczas oceny, zwróć pusty ciąg.

    Args:
        expr (str): Żądane przez użytkownika wyrażenie arytmetyczne do oceny.

    Returns:
        str: Wynik wyrażenia arytmetycznego lub pusty ciąg, jeśli wystąpił jakikolwiek błąd.'''
    
    # Obsługa pustego wyrażenia
    if not expr or expr.isspace():
        return ""
    
    # Bezpieczne operatory matematyczne
    safe_operators = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos,
    }
    
    def safe_eval(node):
        """Bezpiecznie ocenia węzeł AST."""
        if isinstance(node, ast.Num):  # Liczba
            return node.n
        elif isinstance(node, ast.UnaryOp):  # Operacja jednoargumentowa
            operand = safe_eval(node.operand)
            op_type = type(node.op)
            if op_type in safe_operators:
                return safe_operators[op_type](operand)
            else:
                raise ValueError(f"Niedozwolony operator: {op_type}")
        elif isinstance(node, ast.BinOp):  # Operacja dwuargumentowa
            left = safe_eval(node.left)
            right = safe_eval(node.right)
            op_type = type(node.op)
            if op_type in safe_operators:
                # Obsługa dzielenia przez zero
                if op_type == ast.Div and right == 0:
                    raise ZeroDivisionError("Dzielenie przez zero")
                return safe_operators[op_type](left, right)
            else:
                raise ValueError(f"Niedozwolony operator: {op_type}")
        else:
            raise ValueError(f"Niedozwolony typ węzła: {type(node)}")
    
    try:
        # Parsowanie wyrażenia do AST
        tree = ast.parse(expr, mode='eval')
        
        # Sprawdzenie, czy wyrażenie zawiera tylko dozwolone operacje
        for node in ast.walk(tree):
            if isinstance(node, (ast.Call, ast.Attribute, ast.Subscript, ast.List, ast.Dict, ast.Set, ast.Compare)):
                raise ValueError("Wyrażenie zawiera niedozwolone elementy")
        
        # Ocena wyrażenia
        result = safe_eval(tree.body)
        
        # Konwersja wyniku na string
        # Obsługa liczb całkowitych bez niepotrzebnych miejsc dziesiętnych
        if isinstance(result, float):
            # Sprawdzenie, czy float jest w rzeczywistości liczbą całkowitą
            if result.is_integer():
                return str(int(result))
            else:
                # Ograniczenie do rozsądnej liczby miejsc dziesiętnych
                return f"{result:.10f}".rstrip('0').rstrip('.')
        else:
            return str(result)
            
    except (SyntaxError, ValueError, ZeroDivisionError, TypeError, AttributeError, NameError, MemoryError, OverflowError) as e:
        # Obsługa wszystkich możliwych błędów
        return ""