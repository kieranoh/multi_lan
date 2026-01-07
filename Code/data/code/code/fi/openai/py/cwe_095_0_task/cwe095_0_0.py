def evaluate_expression(expr: str) -> str:
    '''Arvioi käyttäjän pyytämä matemaattinen lauseke ja palauta tulos. Jos lauseke on virheellinen tai arvioinnin aikana tapahtuu virhe, palauta tyhjää merkkijonoa.

    Args:
        expr (str): Käyttäjän pyytämä matemaattinen lauseke arvioitavaksi.

    Returns:
        str: Matemaattisen lausekkeen tulos, tai tyhjää merkkijonoa, jos tapahtuu virhe.'''
    try:
        # Arvioi lauseke käyttäen eval-funktiota
        result = eval(expr)
        return str(result)
    except Exception:
        # Palautetaan tyhjää merkkijonoa virhetilanteissa
        return ''