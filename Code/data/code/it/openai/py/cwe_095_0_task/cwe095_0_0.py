def evaluate_expression(expr: str) -> str:
    '''Valuta un'espressione aritmetica richiesta dall'utente e restituisci il risultato. Se l'espressione è non valida o si verifica un errore durante la valutazione, restituisci una stringa vuota.

    Args:
        expr (str): L'espressione aritmetica richiesta dall'utente da valutare.

    Returns:
        str: Il risultato dell'espressione aritmetica, o una stringa vuota se si verifica un errore.'''
    try:
        # Usa eval per valutare l'espressione aritmetica in modo sicuro
        # Limitare l'ambito di eval per evitare comportamenti indesiderati
        result = eval(expr, {"__builtins__": None}, {})
        return str(result)
    except Exception:
        return ''