import re
import operator

def evaluate_expression(expr: str) -> str:
    '''评估用户请求的算术表达式并返回结果。如果表达式无效或在评估过程中发生任何错误，则返回空字符串。

    Args:
        expr (str): 要评估的用户请求的算术表达式。

    Returns:
        str: 算术表达式的结果，如果发生任何错误则返回空字符串。'''
    
    # 如果表达式为空或只包含空白字符，返回空字符串
    if not expr or expr.isspace():
        return ""
    
    # 清理表达式：移除空白字符
    expr = expr.strip()
    
    # 安全检查：防止执行任意代码
    # 只允许数字、基本运算符、括号和小数点
    allowed_chars = set('0123456789+-*/(). ')
    if not all(c in allowed_chars for c in expr):
        return ""
    
    # 进一步验证表达式结构
    # 检查括号是否匹配
    stack = []
    for char in expr:
        if char == '(':
            stack.append(char)
        elif char == ')':
            if not stack:
                return ""  # 右括号没有匹配的左括号
            stack.pop()
    
    if stack:  # 左括号没有匹配的右括号
        return ""
    
    # 检查是否有连续的操作符（除了负号）
    # 简化检查：不允许两个操作符连续出现（负号除外）
    expr_no_spaces = expr.replace(' ', '')
    for i in range(len(expr_no_spaces) - 1):
        if expr_no_spaces[i] in '+-*/' and expr_no_spaces[i + 1] in '+-*/':
            # 检查是否是负号的情况：'-'后面跟着数字或'('
            if expr_no_spaces[i] == '-' and (expr_no_spaces[i + 1].isdigit() or expr_no_spaces[i + 1] == '('):
                continue
            return ""
    
    try:
        # 使用eval计算表达式，但限制其功能
        # 创建安全的环境，只允许基本数学运算
        safe_dict = {
            '__builtins__': None,
            'abs': abs,
            'round': round,
            'int': int,
            'float': float,
        }
        
        # 添加数学运算符
        safe_dict.update({
            '+': operator.add,
            '-': operator.sub,
            '*': operator.mul,
            '/': operator.truediv,
        })
        
        # 使用eval计算表达式
        result = eval(expr, {"__builtins__": {}}, safe_dict)
        
        # 处理除零错误
        if isinstance(result, float) and (result == float('inf') or result == float('-inf')):
            return ""
        
        # 将结果转换为字符串
        # 如果是整数，返回整数形式；如果是浮点数，保留适当精度
        if isinstance(result, int):
            return str(result)
        elif isinstance(result, float):
            # 检查是否为NaN
            if result != result:  # NaN不等于自身
                return ""
            # 如果是整数浮点数，返回整数形式
            if result.is_integer():
                return str(int(result))
            # 否则返回适当精度的浮点数
            # 使用repr确保精度，但移除不必要的尾随零
            result_str = repr(result)
            if 'e' not in result_str and '.' in result_str:
                # 移除尾随的零
                result_str = result_str.rstrip('0').rstrip('.')
            return result_str
        else:
            # 如果结果不是数字类型，返回空字符串
            return ""
            
    except ZeroDivisionError:
        return ""
    except SyntaxError:
        return ""
    except NameError:
        return ""
    except TypeError:
        return ""
    except ValueError:
        return ""
    except Exception:
        # 捕获所有其他异常
        return ""