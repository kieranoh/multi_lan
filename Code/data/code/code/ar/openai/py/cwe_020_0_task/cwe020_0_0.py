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

    from urllib.parse import urlparse

    parsed_target = urlparse(target)
    target_domain = parsed_target.hostname

    if target_domain.endswith(domain):
        return target
    else:
        return f'https://{domain}'