import re
import math

def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if the any error occurs.
    '''
    # Helper function to safely evaluate the expression
    def safe_eval(expression: str) -> str:
        # Define allowed characters and patterns
        allowed_pattern = r'^[\d\s\+\-\*\/\(\)\.\^\%\s]+$'
        
        # Check if expression contains only allowed characters
        if not re.match(allowed_pattern, expression):
            return ""
        
        # Replace ^ with ** for exponentiation
        expression = expression.replace('^', '**')
        
        # Define allowed names for eval (only math functions and constants we want to allow)
        allowed_names = {
            'abs': abs,
            'round': round,
            'pow': pow,
            'max': max,
            'min': min,
            'sqrt': math.sqrt,
            'pi': math.pi,
            'e': math.e,
            'sin': math.sin,
            'cos': math.cos,
            'tan': math.tan,
            'log': math.log,
            'log10': math.log10,
            'exp': math.exp,
        }
        
        # Create a safe eval environment
        safe_env = {
            '__builtins__': {},
            'math': math,
        }
        safe_env.update(allowed_names)
        
        try:
            # Evaluate the expression
            result = eval(expression, safe_env)
            
            # Handle division by zero
            if isinstance(result, (int, float)) and (math.isinf(result) or math.isnan(result)):
                return ""
            
            # Convert result to string
            if isinstance(result, float):
                # Check if it's an integer represented as float
                if result.is_integer():
                    return str(int(result))
                # Otherwise format to reasonable precision
                return str(round(result, 10)).rstrip('0').rstrip('.')
            else:
                return str(result)
                
        except Exception:
            return ""
    
    # Clean the input expression
    if not expr or not isinstance(expr, str):
        return ""
    
    # Remove any leading/trailing whitespace
    expr = expr.strip()
    
    # Check if expression is empty after stripping
    if not expr:
        return ""
    
    # Evaluate the expression safely
    result = safe_eval(expr)
    
    # Return empty string if evaluation failed
    if result == "":
        return ""
    
    return result