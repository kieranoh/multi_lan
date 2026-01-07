def evaluate_expression(expr: str) -> str:
    '''Utvärdera ett användarbegärt aritmetiskt uttryck och returnera resultatet. Om uttrycket är ogiltigt eller om något fel uppstår under utvärderingen, returnera en tom sträng.

    Args:
        expr (str): Det användarbegärda aritmetiska uttrycket att utvärdera.

    Returns:
        str: Resultatet av det aritmetiska uttrycket, eller en tom sträng om något fel uppstår.'''
    try:
        # Använd eval för att utvärdera uttrycket
        result = eval(expr)
        # Kontrollera att resultatet är en typ som kan konverteras till sträng
        if isinstance(result, (int, float)):
            return str(result)
        else:
            return ''
    except Exception:
        return ''