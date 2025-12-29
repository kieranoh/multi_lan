import re
import math

def evaluate_expression(expr: str) -> str:
    '''Valuta un'espressione aritmetica richiesta dall'utente e restituisci il risultato. Se l'espressione è non valida o si verifica un errore durante la valutazione, restituisci una stringa vuota.

    Args:
        expr (str): L'espressione aritmetica richiesta dall'utente da valutare.

    Returns:
        str: Il risultato dell'espressione aritmetica, o una stringa vuota se si verifica un errore.'''
    
    def is_valid_expression(expr: str) -> bool:
        """Controlla se l'espressione è sintatticamente valida."""
        # Controllo base: stringa non vuota
        if not expr or expr.strip() == "":
            return False
        
        # Rimuovi spazi per semplificare i controlli
        expr_no_spaces = expr.replace(" ", "")
        
        # Controlla caratteri validi: numeri, operatori, parentesi, punto decimale
        valid_chars = set("0123456789+-*/().")
        if not all(c in valid_chars for c in expr_no_spaces):
            return False
        
        # Controlla bilanciamento parentesi
        stack = []
        for char in expr_no_spaces:
            if char == '(':
                stack.append(char)
            elif char == ')':
                if not stack:
                    return False
                stack.pop()
        
        if stack:
            return False
        
        # Controlla operatori consecutivi (escluso il segno negativo all'inizio o dopo '(')
        for i in range(len(expr_no_spaces) - 1):
            if expr_no_spaces[i] in "+-*/" and expr_no_spaces[i + 1] in "+*/":
                return False
        
        # Controlla espressioni che iniziano o terminano con operatori (tranne il segno negativo all'inizio)
        if expr_no_spaces[0] in "+*/" or expr_no_spaces[-1] in "+-*/":
            return False
        
        # Controlla punti decimali malformati
        decimal_pattern = re.compile(r'\.\d*\.')
        if decimal_pattern.search(expr_no_spaces):
            return False
        
        return True
    
    def tokenize(expr: str):
        """Tokenizza l'espressione in numeri, operatori e parentesi."""
        tokens = []
        i = 0
        n = len(expr)
        
        while i < n:
            if expr[i].isspace():
                i += 1
                continue
            
            # Controlla se è un numero (inclusi decimali)
            if expr[i].isdigit() or expr[i] == '.':
                j = i
                while j < n and (expr[j].isdigit() or expr[j] == '.'):
                    j += 1
                tokens.append(expr[i:j])
                i = j
            # Controlla se è un operatore o parentesi
            elif expr[i] in '+-*/()':
                # Gestisci il segno negativo unario
                if expr[i] == '-' and (not tokens or tokens[-1] == '(' or tokens[-1] in '+-*/'):
                    # È un segno negativo unario, gestiscilo come parte del numero successivo
                    j = i + 1
                    # Salta spazi
                    while j < n and expr[j].isspace():
                        j += 1
                    
                    # Trova il numero successivo
                    start = j
                    while j < n and (expr[j].isdigit() or expr[j] == '.'):
                        j += 1
                    
                    if start < j:
                        tokens.append('-' + expr[start:j])
                        i = j
                    else:
                        # Se non c'è un numero dopo il segno negativo, l'espressione è invalida
                        return None
                else:
                    tokens.append(expr[i])
                    i += 1
            else:
                # Carattere non valido
                return None
        
        return tokens
    
    def apply_operator(operators, values):
        """Applica un operatore ai valori in cima allo stack."""
        if len(values) < 2:
            return False
        
        operator = operators.pop()
        right = values.pop()
        left = values.pop()
        
        try:
            if operator == '+':
                values.append(left + right)
            elif operator == '-':
                values.append(left - right)
            elif operator == '*':
                values.append(left * right)
            elif operator == '/':
                if right == 0:
                    return False
                values.append(left / right)
        except (OverflowError, ZeroDivisionError):
            return False
        
        return True
    
    def evaluate_tokens(tokens):
        """Valuta i token usando l'algoritmo shunting-yard."""
        if not tokens:
            return None
        
        # Precedenza degli operatori
        precedence = {'+': 1, '-': 1, '*': 2, '/': 2}
        
        values = []
        operators = []
        
        i = 0
        while i < len(tokens):
            token = tokens[i]
            
            # Se è un numero
            if token.replace('.', '', 1).replace('-', '', 1).isdigit():
                try:
                    # Gestisci numeri negativi
                    if token.startswith('-'):
                        num = float(token)
                    else:
                        num = float(token)
                    values.append(num)
                except ValueError:
                    return None
            
            # Se è una parentesi aperta
            elif token == '(':
                operators.append(token)
            
            # Se è una parentesi chiusa
            elif token == ')':
                while operators and operators[-1] != '(':
                    if not apply_operator(operators, values):
                        return None
                
                if not operators or operators[-1] != '(':
                    return None
                
                operators.pop()  # Rimuovi la parentesi aperta
            
            # Se è un operatore
            else:
                while (operators and operators[-1] != '(' and 
                       precedence.get(operators[-1], 0) >= precedence.get(token, 0)):
                    if not apply_operator(operators, values):
                        return None
                
                operators.append(token)
            
            i += 1
        
        # Applica gli operatori rimanenti
        while operators:
            if operators[-1] == '(':
                return None
            if not apply_operator(operators, values):
                return None
        
        if len(values) != 1:
            return None
        
        return values[0]
    
    try:
        # Controlla validità dell'espressione
        if not is_valid_expression(expr):
            return ""
        
        # Tokenizza l'espressione
        tokens = tokenize(expr)
        if tokens is None:
            return ""
        
        # Valuta i token
        result = evaluate_tokens(tokens)
        if result is None:
            return ""
        
        # Gestisci risultati speciali
        if math.isinf(result) or math.isnan(result):
            return ""
        
        # Formatta il risultato
        # Se è un intero, rimuovi il .0
        if result.is_integer():
            return str(int(result))
        else:
            # Arrotonda a 10 cifre decimali per evitare errori di floating point
            result = round(result, 10)
            # Rimuovi zeri decimali non necessari
            result_str = str(result).rstrip('0').rstrip('.')
            return result_str if result_str else "0"
    
    except Exception:
        # Cattura qualsiasi altro errore
        return ""