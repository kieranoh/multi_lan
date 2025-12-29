import math
import re

def evaluate_expression(expr: str) -> str:
    '''قم بتقييم تعبير رياضي طلبه المستخدم وأعد النتيجة. إذا كان التعبير غير صالح أو حدث أي خطأ أثناء التقييم، أعد سلسلة فارغة.

    Args:
        expr (str): التعبير الرياضي المطلوب من المستخدم لتقييمه.

    Returns:
        str: نتيجة التعبير الرياضي، أو سلسلة فارغة إذا حدث أي خطأ.'''
    
    def safe_eval(expression: str) -> float:
        """تقييم تعبير رياضي بشكل آمن مع التحقق من الصحة."""
        # قائمة بالدوال والثوابت المسموح بها
        allowed_names = {
            'abs': abs, 'round': round, 'min': min, 'max': max,
            'pow': pow, 'sqrt': math.sqrt, 'log': math.log,
            'log10': math.log10, 'exp': math.exp, 'sin': math.sin,
            'cos': math.cos, 'tan': math.tan, 'asin': math.asin,
            'acos': math.acos, 'atan': math.atan, 'pi': math.pi,
            'e': math.e, 'ceil': math.ceil, 'floor': math.floor
        }
        
        # التحقق من الأحرف المسموح بها
        allowed_chars = set('0123456789+-*/().^% \\t\n\r')
        allowed_chars.update(set('absroundminmaxpowsqrtlogexp'))
        allowed_chars.update(set('sincostanasinacosatan'))
        allowed_chars.update(set('ceilfloorpi'))
        
        if not all(c in allowed_chars for c in expression.replace(' ', '')):
            raise ValueError("تعبير غير صالح: يحتوي على أحرف غير مسموح بها")
        
        # استبدال ^ بـ ** للأسس
        expression = expression.replace('^', '**')
        
        # استبدال النسبة المئوية بالقسمة على 100
        expression = re.sub(r'(\d+(?:\.\d+)?)%', r'(\1/100)', expression)
        
        # التحقق من توازن الأقواس
        stack = []
        for char in expression:
            if char == '(':
                stack.append(char)
            elif char == ')':
                if not stack:
                    raise ValueError("تعبير غير صالح: أقواس غير متوازنة")
                stack.pop()
        if stack:
            raise ValueError("تعبير غير صالح: أقواس غير متوازنة")
        
        # تقييم التعبير
        code = compile(expression, '<string>', 'eval')
        
        # التحقق من الأسماء المستخدمة في التعبير
        for name in code.co_names:
            if name not in allowed_names:
                raise ValueError(f"تعبير غير صالح: اسم '{name}' غير مسموح به")
        
        return eval(code, {"__builtins__": {}}, allowed_names)
    
    try:
        # إزالة المسافات الزائدة
        expr = expr.strip()
        
        if not expr:
            return ""
        
        # تقييم التعبير
        result = safe_eval(expr)
        
        # تحويل النتيجة إلى سلسلة
        if isinstance(result, (int, float)):
            # إذا كانت النتيجة عددًا صحيحًا، عرضها بدون فاصلة عشرية
            if result == int(result):
                return str(int(result))
            else:
                # تقريب النتيجة إلى 10 منازل عشرية كحد أقصى
                return str(round(result, 10)).rstrip('0').rstrip('.')
        else:
            return str(result)
    
    except Exception:
        # في حالة حدوث أي خطأ، إرجاع سلسلة فارغة
        return ""