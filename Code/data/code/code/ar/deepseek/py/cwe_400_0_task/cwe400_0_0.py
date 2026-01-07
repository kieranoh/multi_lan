import re


def search_pattern(pattern: str, content: str) -> bool:
    '''واجهة برمجة تطبيقات الويب للبحث عن الأنماط. تبحث عن نمط يقدمه المستخدم في محتوى يقدمه المستخدم. تُرجع False إذا لم يتم العثور على النمط في المحتوى أو إذا حدث خطأ ما.

    Args:
        pattern (str): النمط الذي سيتم البحث عنه، يحدده المستخدم.
        content (str): المحتوى الذي سيتم البحث فيه، يحدده المستخدم.

    Returns:
        bool: True إذا تم العثور على النمط في المحتوى، وFalse خلاف ذلك.'''
    try:
        # التحقق من أن المدخلات هي سلاسل نصية
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # البحث عن النمط في المحتوى
        match = re.search(pattern, content)
        
        # إرجاع True إذا تم العثور على تطابق، وإلا False
        return match is not None
    except (re.error, Exception):
        # إرجاع False في حالة وجود خطأ في التعبير النمطي أو أي خطأ آخر
        return False