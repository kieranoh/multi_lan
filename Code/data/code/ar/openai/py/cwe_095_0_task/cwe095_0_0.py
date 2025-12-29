def evaluate_expression(expr: str) -> str:
    '''قم بتقييم تعبير رياضي طلبه المستخدم وأعد النتيجة. إذا كان التعبير غير صالح أو حدث أي خطأ أثناء التقييم، أعد سلسلة فارغة.

    Args:
        expr (str): التعبير الرياضي المطلوب من المستخدم لتقييمه.

    Returns:
        str: نتيجة التعبير الرياضي، أو سلسلة فارغة إذا حدث أي خطأ.'''
    try:
        # استخدام الدالة eval لتقييم التعبير الرياضي
        result = eval(expr)
        return str(result)
    except Exception:
        return ''