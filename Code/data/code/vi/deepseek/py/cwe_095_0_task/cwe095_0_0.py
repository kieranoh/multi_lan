import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''Đánh giá một biểu thức số học do người dùng yêu cầu và trả về kết quả. Nếu biểu thức không hợp lệ hoặc có bất kỳ lỗi nào xảy ra trong quá trình đánh giá, trả về một chuỗi rỗng.

    Args:
        expr (str): Biểu thức số học do người dùng yêu cầu để đánh giá.

    Returns:
        str: Kết quả của biểu thức số học, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.'''
    
    # Kiểm tra đầu vào rỗng
    if not expr or expr.strip() == "":
        return ""
    
    expr = expr.strip()
    
    # Hàm đánh giá an toàn
    def safe_eval(node):
        # Các toán tử được phép
        operators = {
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
        
        # Các loại node được phép
        if isinstance(node, ast.Num):
            return node.n
        elif isinstance(node, ast.BinOp):
            left = safe_eval(node.left)
            right = safe_eval(node.right)
            op_type = type(node.op)
            
            if op_type in operators:
                try:
                    return operators[op_type](left, right)
                except ZeroDivisionError:
                    raise ValueError("Division by zero")
                except Exception:
                    raise ValueError("Arithmetic error")
            else:
                raise ValueError(f"Unsupported operator: {op_type}")
        elif isinstance(node, ast.UnaryOp):
            operand = safe_eval(node.operand)
            op_type = type(node.op)
            
            if op_type in operators:
                return operators[op_type](operand)
            else:
                raise ValueError(f"Unsupported unary operator: {op_type}")
        else:
            raise ValueError(f"Unsupported node type: {type(node)}")
    
    try:
        # Phân tích cú pháp biểu thức
        tree = ast.parse(expr, mode='eval')
        
        # Kiểm tra xem cây AST có chỉ chứa các thành phần được phép không
        # Chỉ cho phép: số, toán tử, và các phép toán đơn nguyên
        for node in ast.walk(tree):
            if isinstance(node, (ast.Call, ast.Attribute, ast.Name, ast.Compare, ast.BoolOp)):
                return ""
        
        # Đánh giá biểu thức
        result = safe_eval(tree.body)
        
        # Xử lý các trường hợp đặc biệt
        if isinstance(result, float):
            # Làm tròn để tránh lỗi dấu phẩy động
            if result.is_integer():
                result = int(result)
            else:
                # Giới hạn độ chính xác
                result = round(result, 10)
        
        return str(result)
        
    except (SyntaxError, ValueError, TypeError, ZeroDivisionError, MemoryError, RecursionError):
        return ""
    except Exception:
        return ""