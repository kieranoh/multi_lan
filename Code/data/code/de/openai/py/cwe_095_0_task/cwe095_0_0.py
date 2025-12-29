def evaluate_expression(expr: str) -> str:
    '''Bewerte einen vom Benutzer angeforderten arithmetischen Ausdruck und gib das Ergebnis zurück. Wenn der Ausdruck ungültig ist oder während der Auswertung ein Fehler auftritt, gib einen leeren String zurück.

    Args:
        expr (str): Der vom Benutzer angeforderte arithmetische Ausdruck zur Auswertung.

    Returns:
        str: Das Ergebnis des arithmetischen Ausdrucks oder ein leerer String, wenn ein Fehler auftritt.'''
    
    try:
        result = eval(expr)
        return str(result)
    except Exception:
        return ''