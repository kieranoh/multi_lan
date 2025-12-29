import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''یک عبارت حسابی درخواست شده توسط کاربر را ارزیابی کرده و نتیجه را برگردانید. اگر عبارت نامعتبر باشد یا در حین ارزیابی خطایی رخ دهد، یک رشته خالی برگردانید.

    Args:
        expr (str): عبارت حسابی درخواست شده توسط کاربر برای ارزیابی.

    Returns:
        str: نتیجه عبارت حسابی، یا یک رشته خالی اگر خطایی رخ دهد.'''
    
    # تعریف عملگرهای مجاز برای امنیت
    ALLOWED_OPERATORS = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos
    }
    
    def safe_eval(node):
        """تابع بازگشتی برای ارزیابی امن گره‌های AST"""
        if isinstance(node, ast.Num):  # برای اعداد (Python 3.7 و پایین‌تر)
            return node.n
        elif isinstance(node, ast.Constant):  # برای اعداد (Python 3.8+)
            return node.value
        elif isinstance(node, ast.BinOp):
            try:
                left = safe_eval(node.left)
                right = safe_eval(node.right)
                op_type = type(node.op)
                if op_type in ALLOWED_OPERATORS:
                    return ALLOWED_OPERATORS[op_type](left, right)
                else:
                    raise ValueError(f"عملگر غیرمجاز: {op_type}")
            except ZeroDivisionError:
                raise ValueError("تقسیم بر صفر")
            except Exception:
                raise ValueError("خطا در محاسبه")
        elif isinstance(node, ast.UnaryOp):
            operand = safe_eval(node.operand)
            op_type = type(node.op)
            if op_type in ALLOWED_OPERATORS:
                return ALLOWED_OPERATORS[op_type](operand)
            else:
                raise ValueError(f"عملگر یکانی غیرمجاز: {op_type}")
        else:
            raise ValueError("ساختار عبارت غیرمجاز")
    
    try:
        # حذف فضاهای اضافی
        expr = expr.strip()
        if not expr:
            return ""
        
        # تجزیه عبارت به AST
        tree = ast.parse(expr, mode='eval')
        
        # بررسی امنیت: فقط اجازه گره‌های Expression با بدنه مجاز
        if not isinstance(tree, ast.Expression):
            return ""
        
        # ارزیابی امن
        result = safe_eval(tree.body)
        
        # تبدیل نتیجه به رشته
        # برای اعداد صحیح، نمایش بدون اعشار
        if isinstance(result, int):
            return str(result)
        # برای اعداد اعشاری، نمایش با حداکثر 10 رقم اعشار
        elif isinstance(result, float):
            # حذف صفرهای اضافی در انتها
            formatted = f"{result:.10f}".rstrip('0').rstrip('.')
            return formatted
        else:
            # برای سایر انواع (در صورت وجود)
            return str(result)
            
    except (SyntaxError, ValueError, TypeError, MemoryError, RecursionError, 
            ZeroDivisionError, OverflowError, NameError, AttributeError):
        # تمام خطاهای احتمالی را بگیر و رشته خالی برگردان
        return ""