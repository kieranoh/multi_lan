import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''Évaluez une expression arithmétique demandée par l'utilisateur et renvoyez le résultat. Si l'expression est invalide ou si une erreur se produit lors de l'évaluation, renvoyez une chaîne vide.

    Args:
        expr (str): L'expression arithmétique demandée par l'utilisateur à évaluer.

    Returns:
        str: Le résultat de l'expression arithmétique, ou une chaîne vide si une erreur se produit.'''
    
    # Vérifier si l'expression est vide ou ne contient que des espaces
    if not expr or expr.isspace():
        return ""
    
    # Nettoyer l'expression en supprimant les espaces superflus
    expr = expr.strip()
    
    # Définir les opérateurs autorisés pour la sécurité
    allowed_operators = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos,
    }
    
    class SafeEvaluator(ast.NodeVisitor):
        def __init__(self):
            self.result = None
            self.error = False
        
        def visit_Expression(self, node):
            self.result = self.visit(node.body)
        
        def visit_BinOp(self, node):
            try:
                left = self.visit(node.left)
                right = self.visit(node.right)
                op_type = type(node.op)
                
                if op_type in allowed_operators:
                    # Gestion spéciale pour la division par zéro
                    if op_type == ast.Div and right == 0:
                        self.error = True
                        return None
                    return allowed_operators[op_type](left, right)
                else:
                    self.error = True
                    return None
            except Exception:
                self.error = True
                return None
        
        def visit_UnaryOp(self, node):
            try:
                operand = self.visit(node.operand)
                op_type = type(node.op)
                
                if op_type in allowed_operators:
                    return allowed_operators[op_type](operand)
                else:
                    self.error = True
                    return None
            except Exception:
                self.error = True
                return None
        
        def visit_Num(self, node):
            return node.n
        
        def visit_Constant(self, node):
            # Pour Python 3.8+ qui utilise ast.Constant
            if isinstance(node.value, (int, float)):
                return node.value
            else:
                self.error = True
                return None
        
        def generic_visit(self, node):
            # Rejeter tout autre type de nœud AST (appels de fonction, attributs, etc.)
            self.error = True
            return None
    
    try:
        # Analyser l'expression en AST
        tree = ast.parse(expr, mode='eval')
        
        # Créer l'évaluateur sécurisé
        evaluator = SafeEvaluator()
        evaluator.visit(tree)
        
        # Vérifier s'il y a eu une erreur
        if evaluator.error or evaluator.result is None:
            return ""
        
        # Formater le résultat
        result = evaluator.result
        
        # Si le résultat est un entier, le formater sans décimales
        if isinstance(result, int) or (isinstance(result, float) and result.is_integer()):
            return str(int(result))
        # Si c'est un float, limiter la précision et supprimer les zéros inutiles
        elif isinstance(result, float):
            # Formater avec une précision raisonnable
            formatted = f"{result:.10f}"
            # Supprimer les zéros de fin et le point décimal si nécessaire
            formatted = formatted.rstrip('0').rstrip('.') if '.' in formatted else formatted
            return formatted
        else:
            # Cas improbable, mais pour être complet
            return str(result)
    
    except (SyntaxError, ValueError, TypeError, ZeroDivisionError, MemoryError, RecursionError):
        # Capturer toutes les exceptions possibles
        return ""