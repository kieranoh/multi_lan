import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''Avalie uma expressão aritmética solicitada pelo usuário e retorne o resultado. Se a expressão for inválida ou ocorrer algum erro durante a avaliação, retorne uma string vazia.

    Args:
        expr (str): A expressão aritmética solicitada pelo usuário para avaliar.

    Returns:
        str: O resultado da expressão aritmética, ou uma string vazia se ocorrer algum erro.'''
    
    # Operadores suportados
    supported_operators = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.FloorDiv: operator.floordiv,
        ast.Mod: operator.mod,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos
    }
    
    # Função para avaliar nós da AST
    def eval_node(node):
        if isinstance(node, ast.Num):  # Número (int ou float)
            return node.n
        elif isinstance(node, ast.BinOp):  # Operação binária
            try:
                left = eval_node(node.left)
                right = eval_node(node.right)
                op_type = type(node.op)
                
                if op_type not in supported_operators:
                    raise ValueError(f"Operador {op_type} não suportado")
                
                # Verificar divisão por zero
                if op_type == ast.Div and right == 0:
                    raise ZeroDivisionError("Divisão por zero")
                elif op_type == ast.FloorDiv and right == 0:
                    raise ZeroDivisionError("Divisão por zero")
                elif op_type == ast.Mod and right == 0:
                    raise ZeroDivisionError("Módulo por zero")
                
                return supported_operators[op_type](left, right)
            except (ValueError, ZeroDivisionError, TypeError):
                raise
        elif isinstance(node, ast.UnaryOp):  # Operação unária
            try:
                operand = eval_node(node.operand)
                op_type = type(node.op)
                
                if op_type not in supported_operators:
                    raise ValueError(f"Operador unário {op_type} não suportado")
                
                return supported_operators[op_type](operand)
            except (ValueError, TypeError):
                raise
        else:
            raise ValueError(f"Tipo de nó {type(node)} não suportado")
    
    try:
        # Verificar se a string está vazia ou contém apenas espaços
        if not expr or expr.isspace():
            return ""
        
        # Analisar a expressão em uma AST
        tree = ast.parse(expr, mode='eval')
        
        # Avaliar a expressão
        result = eval_node(tree.body)
        
        # Converter o resultado para string
        # Para números inteiros, remover o .0 se for o caso
        if isinstance(result, float) and result.is_integer():
            return str(int(result))
        else:
            return str(result)
            
    except (SyntaxError, ValueError, ZeroDivisionError, TypeError, 
            AttributeError, MemoryError, RecursionError, 
            OverflowError, KeyError, IndexError):
        # Capturar todos os erros possíveis e retornar string vazia
        return ""