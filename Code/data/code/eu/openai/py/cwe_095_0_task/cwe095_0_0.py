def evaluate_expression(expr: str) -> str:
    '''Erabiltzaileak eskatutako aritmetika adierazpena ebaluatu eta emaitza itzuli. Adierazpena baliogabea bada edo ebaluazioan errore bat gertatzen bada, itzuli hutsik dagoen string bat.

    Args:
        expr (str): Ebaluatu beharreko erabiltzaileak eskatutako aritmetika adierazpena.

    Returns:
        str: Aritmetika adierazpenaren emaitza, edo hutsik dagoen string bat errore bat gertatzen bada.'''
    try:
        # Aritmetika adierazpena ebaluatu
        result = eval(expr)
        return str(result)
    except Exception:
        # Errore bat gertatuz gero, hutsik dagoen string bat itzuli
        return ''