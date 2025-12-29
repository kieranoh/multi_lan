import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """تحقق مما إذا كانت عنوان البريد الإلكتروني المقدم صالحًا. على سبيل المثال، abc.123@def.ghi.com.uk هو عنوان بريد إلكتروني صالح. غطِّ أكبر عدد ممكن من الحالات لتجنب النتائج السلبية الخاطئة.

    Args:
        email: البريد الإلكتروني الذي سيتم التحقق منه.

    Returns:
        Tuple[bool, str]: مجموعة تحتوي على العنصر الأول وهو قيمة منطقية تشير إلى ما إذا كان البريد الإلكتروني صالحًا والعنصر الثاني هو النمط المستخدم للتحقق من البريد الإلكتروني."""
    
    # نمط شامل للتحقق من صحة البريد الإلكتروني
    # يتبع RFC 5322 بشكل عام مع بعض التبسيط للاستخدام العملي
    pattern = r"""
        ^                       # بداية السلسلة
        [a-zA-Z0-9]             # يجب أن يبدأ بحرف أو رقم
        (                       # مجموعة للجزء المحلي (قبل @)
            [a-zA-Z0-9._%+-]*   # أحرف، أرقام، ونقاط، شرطات، علامات مئوية، زائد
            [a-zA-Z0-9._%+-]?   # حرف واحد على الأقل إضافي (اختياري)
        )?                      # الجزء المحلي كامل (اختياري للسماح بأسماء مستخدم قصيرة)
        @                       # رمز @ المطلوب
        [a-zA-Z0-9]             # يجب أن يبدأ اسم النطاق بحرف أو رقم
        (                       # مجموعة للنطاق
            [a-zA-Z0-9.-]*      # أحرف، أرقام، شرطات، ونقاط
            \.                  # نقطة قبل نطاق المستوى الأعلى
            [a-zA-Z]{2,}        # نطاق المستوى الأعلى (حرفين على الأقل)
            (\.                 # نطاقات مستوى أعلى إضافية (اختيارية)
                [a-zA-Z]{2,}    # نطاق مستوى أعلى إضافي
            )*                  # صفر أو أكثر من نطاقات المستوى الأعلى الإضافية
        )                       # نهاية مجموعة النطاق
        $                       # نهاية السلسلة
    """
    
    # نمط مبسط للاستخدام مع re.match
    simplified_pattern = r"^[a-zA-Z0-9][a-zA-Z0-9._%+-]*@[a-zA-Z0-9][a-zA-Z0-9.-]*\.[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})*$"
    
    # التحقق من الطول الأساسي
    if not email or len(email) > 254:  # الحد الأقصى للطول حسب RFC 5321
        return False, simplified_pattern
    
    # التحقق من وجود @ واحدة فقط
    if email.count('@') != 1:
        return False, simplified_pattern
    
    # تقسيم البريد الإلكتروني إلى جزء محلي ونطاق
    local_part, domain = email.split('@')
    
    # التحقق من طول الجزء المحلي (الحد الأقصى 64 حرفًا حسب RFC 5321)
    if len(local_part) > 64 or len(local_part) == 0:
        return False, simplified_pattern
    
    # التحقق من أن الجزء المحلي لا يبدأ أو ينتهي بنقطة
    if local_part.startswith('.') or local_part.endswith('.'):
        return False, simplified_pattern
    
    # التحقق من عدم وجود نقطتين متتاليتين في الجزء المحلي
    if '..' in local_part:
        return False, simplified_pattern
    
    # التحقق من النطاق
    if len(domain) > 253 or len(domain) < 1:
        return False, simplified_pattern
    
    # التحقق من أن النطاق لا يبدأ أو ينتهي بشرطة أو نقطة
    if domain.startswith('-') or domain.endswith('-') or domain.startswith('.') or domain.endswith('.'):
        return False, simplified_pattern
    
    # التحقق من عدم وجود نقطتين متتاليتين في النطاق
    if '..' in domain:
        return False, simplified_pattern
    
    # التحقق من أن كل جزء من النطاق يتبع القواعد
    domain_parts = domain.split('.')
    for part in domain_parts:
        # التحقق من طول كل جزء (الحد الأقصى 63 حرفًا)
        if len(part) > 63 or len(part) < 1:
            return False, simplified_pattern
        
        # التحقق من أن الأجزاء لا تبدأ أو تنتهي بشرطة
        if part.startswith('-') or part.endswith('-'):
            return False, simplified_pattern
        
        # التحقق من أن الأجزاء تحتوي فقط على أحرف وأرقام وشرطات
        if not re.match(r'^[a-zA-Z0-9-]+$', part):
            return False, simplified_pattern
    
    # التحقق من أن نطاق المستوى الأعلى يحتوي على حرفين على الأقل
    if len(domain_parts[-1]) < 2:
        return False, simplified_pattern
    
    # التحقق النهائي باستخدام التعبير النمطي
    if re.match(simplified_pattern, email):
        return True, simplified_pattern
    else:
        return False, simplified_pattern