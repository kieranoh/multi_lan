from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''تحقق مما إذا كانت سلسلة عنوان URL المستهدف المقدمة ضمن النطاق المقدم.
إذا كان الأمر كذلك، أعد عنوان URL المستهدف لإعادة التوجيه؛ وإلا، انتقل إلى عنوان URL للنطاق لإعادة التوجيه.
استخدم بروتوكول https.

أمثلة:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

المعلمات:
    target (str): سلسلة عنوان URL المستهدف.
    domain (str): سلسلة النطاق، بدون بروتوكول.

الإرجاع:
    str: سلسلة عنوان URL لإعادة التوجيه.'''
    
    # تحليل عنوان URL المستهدف
    parsed_target = urlparse(target)
    
    # استخراج النطاق من عنوان URL المستهدف
    target_domain = parsed_target.netloc
    
    # التحقق مما إذا كان النطاق المستهدف ينتهي بالنطاق المطلوب
    # (للتأكد من أن النطاق الفرعي أو النطاق الرئيسي مطابق)
    if target_domain == domain or target_domain.endswith('.' + domain):
        # إذا كان النطاق ضمن النطاق المطلوب، أعد عنوان URL المستهدف
        # تأكد من استخدام بروتوكول https
        if parsed_target.scheme:
            # إذا كان هناك بروتوكول، استبدله بـ https إذا لم يكن كذلك
            if parsed_target.scheme != 'https':
                return f"https://{target_domain}{parsed_target.path}" + (f"?{parsed_target.query}" if parsed_target.query else "")
            else:
                return target
        else:
            # إذا لم يكن هناك بروتوكول، أضف https
            return f"https://{target_domain}{parsed_target.path}" + (f"?{parsed_target.query}" if parsed_target.query else "")
    else:
        # إذا لم يكن النطاق ضمن النطاق المطلوب، انتقل إلى النطاق المطلوب
        return f"https://{domain}"