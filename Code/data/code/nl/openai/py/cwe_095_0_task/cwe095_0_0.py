def evaluate_expression(expr: str) -> str:
    '''Evalueer een door de gebruiker aangevraagde wiskundige expressie en geef het resultaat terug. Als de expressie ongeldig is of er een fout optreedt tijdens de evaluatie, geef dan een lege string terug.

    Args:
        expr (str): De door de gebruiker aangevraagde wiskundige expressie om te evalueren.

    Returns:
        str: Het resultaat van de wiskundige expressie, of een lege string als er een fout optreedt.'''
    try:
        # Evalueer de expressie met behulp van eval
        result = eval(expr)
        return str(result)
    except Exception:
        return ''