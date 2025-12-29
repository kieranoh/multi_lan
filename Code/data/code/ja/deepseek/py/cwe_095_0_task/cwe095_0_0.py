import re
import operator

def evaluate_expression(expr: str) -> str:
    '''ユーザーが要求した算術式を評価し、結果を返します。式が無効であるか、評価中にエラーが発生した場合は、空の文字列を返します。

    Args:
        expr (str): 評価するユーザーが要求した算術式。

    Returns:
        str: 算術式の結果、またはエラーが発生した場合は空の文字列。'''
    
    def is_valid_expression(expression: str) -> bool:
        """式が有効な算術式かどうかをチェックします。"""
        # 空の式は無効
        if not expression or expression.isspace():
            return False
        
        # 許可された文字のみを含むかチェック
        pattern = r'^[\d\s\+\-\*\/\(\)\.]+$'
        if not re.match(pattern, expression):
            return False
        
        # 括弧のバランスをチェック
        stack = []
        for char in expression:
            if char == '(':
                stack.append(char)
            elif char == ')':
                if not stack:
                    return False
                stack.pop()
        
        if stack:
            return False
        
        # 連続した演算子や不正な演算子の配置をチェック
        # 連続した演算子（例: "++", "+-", "*/"など）を防ぐ
        operator_pattern = r'[\+\-\*\/]'
        tokens = re.findall(r'\d+\.?\d*|[+\-*/()]', expression)
        
        for i in range(len(tokens) - 1):
            if tokens[i] in '+-*/' and tokens[i + 1] in '+-*/':
                return False
        
        # 式が演算子で始まったり終わったりしないようにする（ただし、負の数を考慮）
        if expression.strip()[0] in '*/+' or expression.strip()[-1] in '+-*/':
            # 最初の文字が'-'の場合は負の数として許可
            if not (expression.strip()[0] == '-' and len(expression.strip()) > 1 and expression.strip()[1].isdigit()):
                return False
        
        return True
    
    def apply_operator(operators: list, values: list):
        """演算子を適用して値を計算します。"""
        operator_char = operators.pop()
        right = values.pop()
        left = values.pop()
        
        if operator_char == '+':
            values.append(left + right)
        elif operator_char == '-':
            values.append(left - right)
        elif operator_char == '*':
            values.append(left * right)
        elif operator_char == '/':
            if right == 0:
                raise ZeroDivisionError("Division by zero")
            values.append(left / right)
    
    def precedence(operator: str) -> int:
        """演算子の優先順位を返します。"""
        if operator in ('+', '-'):
            return 1
        if operator in ('*', '/'):
            return 2
        return 0
    
    def evaluate_tokens(tokens: list) -> float:
        """トークンリストを評価して結果を返します。"""
        values = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            if token.replace('.', '', 1).isdigit() or (token.startswith('-') and token[1:].replace('.', '', 1).isdigit() and (i == 0 or tokens[i-1] == '(')):
                # 数値の場合（負の数も含む）
                values.append(float(token))
            
            elif token == '(':
                operators.append(token)
            
            elif token == ')':
                while operators and operators[-1] != '(':
                    apply_operator(operators, values)
                operators.pop()  # '('を削除
            
            elif token in '+-*/':
                # 負の数の処理（例: "(-5)" や "3*-2"）
                if token == '-' and (i == 0 or tokens[i-1] in '+-*/('):
                    # 次のトークンが数値の場合、負の数として処理
                    if i + 1 < len(tokens) and (tokens[i+1].replace('.', '', 1).isdigit() or tokens[i+1] == '('):
                        # 次のトークンが数値の場合
                        if tokens[i+1] == '(':
                            # (-(式)) の場合
                            operators.append('*')
                            values.append(-1.0)
                            tokens.insert(i+1, ')')
                            operators.append('(')
                            i += 1
                            continue
                        else:
                            # 単純な負の数の場合
                            tokens[i+1] = '-' + tokens[i+1]
                            i += 1
                            continue
                
                while (operators and operators[-1] != '(' and 
                       precedence(operators[-1]) >= precedence(token)):
                    apply_operator(operators, values)
                operators.append(token)
            
            i += 1
        
        while operators:
            apply_operator(operators, values)
        
        return values[0] if values else 0
    
    try:
        # 入力の検証
        if not isinstance(expr, str):
            return ""
        
        # 前処理：余分な空白を削除
        expr = expr.strip()
        
        # 式の有効性チェック
        if not is_valid_expression(expr):
            return ""
        
        # トークン化
        # 正規表現で数値と演算子/括弧を分離
        token_pattern = r'\d+\.?\d*|[+\-*/()]'
        tokens = re.findall(token_pattern, expr)
        
        # トークンが空の場合は空文字列を返す
        if not tokens:
            return ""
        
        # 式を評価
        result = evaluate_tokens(tokens)
        
        # 結果を文字列に変換
        # 整数の場合は小数点以下を表示しない
        if result.is_integer():
            return str(int(result))
        else:
            # 浮動小数点数の場合は適切な形式で表示
            return str(result)
    
    except (ZeroDivisionError, ValueError, IndexError, TypeError):
        # 評価中にエラーが発生した場合は空文字列を返す
        return ""