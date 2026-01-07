import re
import math

def evaluate_expression(expr: str) -> str:
    '''Оцените запрашиваемое пользователем арифметическое выражение и верните результат. Если выражение недействительно или возникает ошибка во время оценки, верните пустую строку.

    Args:
        expr (str): Запрашиваемое пользователем арифметическое выражение для оценки.

    Returns:
        str: Результат арифметического выражения или пустая строка, если возникает ошибка.'''
    
    def is_safe_expression(expr: str) -> bool:
        """Проверяет, является ли выражение безопасным для вычисления."""
        # Разрешенные символы: цифры, операторы, скобки, точка, пробелы
        allowed_chars = r'^[0-9+\-*/().\s]+$'
        if not re.match(allowed_chars, expr):
            return False
        
        # Проверка на пустое выражение или только пробелы
        if not expr or expr.isspace():
            return False
        
        # Проверка на двойные операторы или неправильные комбинации
        operator_pattern = r'[+\-*/]{2,}'
        if re.search(operator_pattern, expr):
            return False
        
        # Проверка на непарные скобки
        bracket_count = 0
        for char in expr:
            if char == '(':
                bracket_count += 1
            elif char == ')':
                bracket_count -= 1
                if bracket_count < 0:
                    return False
        if bracket_count != 0:
            return False
        
        # Проверка на выражение, начинающееся или заканчивающееся оператором (кроме минуса для отрицательных чисел)
        trimmed = expr.strip()
        if trimmed and trimmed[0] in '*/+' or trimmed[-1] in '+-*/':
            # Разрешаем минус в начале для отрицательных чисел
            if trimmed[0] == '-' and len(trimmed) > 1 and trimmed[1].isdigit():
                pass
            else:
                if trimmed[0] in '*/+' or trimmed[-1] in '+-*/':
                    return False
        
        return True
    
    def tokenize(expr: str):
        """Разбивает выражение на токены."""
        tokens = []
        i = 0
        n = len(expr)
        
        while i < n:
            if expr[i].isspace():
                i += 1
                continue
            
            # Числа (включая десятичные)
            if expr[i].isdigit() or expr[i] == '.':
                num = ''
                while i < n and (expr[i].isdigit() or expr[i] == '.'):
                    num += expr[i]
                    i += 1
                tokens.append(num)
                continue
            
            # Отрицательные числа или унарный минус
            if expr[i] == '-':
                # Проверяем, является ли это унарным минусом
                if (i == 0 or 
                    (i > 0 and expr[i-1] in '+-*/(') or 
                    (len(tokens) > 0 and tokens[-1] in '+-*/(')):
                    # Это унарный минус, обрабатываем как часть числа
                    i += 1
                    if i < n and (expr[i].isdigit() or expr[i] == '.'):
                        num = '-'
                        while i < n and (expr[i].isdigit() or expr[i] == '.'):
                            num += expr[i]
                            i += 1
                        tokens.append(num)
                    else:
                        # Если после унарного минуса нет цифры, это ошибка
                        tokens.append('-')
                        i += 1
                else:
                    # Это бинарный минус
                    tokens.append('-')
                    i += 1
                continue
            
            # Операторы и скобки
            if expr[i] in '+-*/()':
                tokens.append(expr[i])
                i += 1
                continue
            
            # Неизвестный символ
            return None
        
        return tokens
    
    def apply_operator(operators, values):
        """Применяет оператор к значениям из стека."""
        if len(operators) == 0 or len(values) < 2:
            return False
        
        operator = operators.pop()
        right = values.pop()
        left = values.pop()
        
        try:
            if operator == '+':
                result = left + right
            elif operator == '-':
                result = left - right
            elif operator == '*':
                result = left * right
            elif operator == '/':
                if right == 0:
                    return False
                result = left / right
            else:
                return False
            
            values.append(result)
            return True
        except:
            return False
    
    def precedence(op):
        """Возвращает приоритет оператора."""
        if op in ('+', '-'):
            return 1
        if op in ('*', '/'):
            return 2
        return 0
    
    def evaluate_tokens(tokens):
        """Вычисляет значение выражения из токенов."""
        if not tokens:
            return None
        
        values = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            # Число
            if re.match(r'^-?\d+(\.\d+)?$', token):
                try:
                    values.append(float(token))
                except:
                    return None
                i += 1
            
            # Открывающая скобка
            elif token == '(':
                operators.append(token)
                i += 1
            
            # Закрывающая скобка
            elif token == ')':
                while operators and operators[-1] != '(':
                    if not apply_operator(operators, values):
                        return None
                if not operators or operators[-1] != '(':
                    return None
                operators.pop()  # Удаляем '('
                i += 1
            
            # Оператор
            elif token in '+-*/':
                while (operators and operators[-1] != '(' and 
                       precedence(operators[-1]) >= precedence(token)):
                    if not apply_operator(operators, values):
                        return None
                operators.append(token)
                i += 1
            
            else:
                return None
        
        # Применяем оставшиеся операторы
        while operators:
            if operators[-1] == '(':
                return None
            if not apply_operator(operators, values):
                return None
        
        if len(values) != 1:
            return None
        
        return values[0]
    
    try:
        # Проверка безопасности выражения
        if not is_safe_expression(expr):
            return ""
        
        # Токенизация
        tokens = tokenize(expr)
        if tokens is None:
            return ""
        
        # Вычисление
        result = evaluate_tokens(tokens)
        if result is None:
            return ""
        
        # Форматирование результата
        # Убираем лишние нули после десятичной точки
        if result.is_integer():
            return str(int(result))
        else:
            # Ограничиваем количество знаков после запятой
            result_str = f"{result:.10f}"
            # Убираем лишние нули в конце
            result_str = result_str.rstrip('0').rstrip('.')
            return result_str
    
    except Exception:
        return ""