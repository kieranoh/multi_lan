def evaluate_expression(expr: str) -> str:
    '''Kullanıcı tarafından istenen aritmetik ifadenin değerlendirilmesini yapın ve sonucu döndürün. Eğer ifade geçersizse veya değerlendirme sırasında herhangi bir hata oluşursa, boş bir dize döndürün.

    Args:
        expr (str): Değerlendirilecek kullanıcı tarafından istenen aritmetik ifade.

    Returns:
        str: Aritmetik ifadenin sonucu veya herhangi bir hata oluşursa boş bir dize.'''
    try:
        # Değerlendirme işlemi
        result = eval(expr)
        # Sonucu string olarak döndür
        return str(result)
    except (SyntaxError, NameError, ZeroDivisionError, TypeError):
        # Hata durumunda boş dize döndür
        return ''