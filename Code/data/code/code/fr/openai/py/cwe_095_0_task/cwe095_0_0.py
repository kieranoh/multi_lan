def evaluate_expression(expr: str) -> str:
    '''Évaluez une expression arithmétique demandée par l'utilisateur et renvoyez le résultat. Si l'expression est invalide ou si une erreur se produit lors de l'évaluation, renvoyez une chaîne vide.

    Args:
        expr (str): L'expression arithmétique demandée par l'utilisateur à évaluer.

    Returns:
        str: Le résultat de l'expression arithmétique, ou une chaîne vide si une erreur se produit.'''
    
    try:
        # Évaluer l'expression en utilisant eval
        result = eval(expr)
        # Convertir le résultat en chaîne
        return str(result)
    except Exception:
        # Si une erreur se produit, retourner une chaîne vide
        return ''