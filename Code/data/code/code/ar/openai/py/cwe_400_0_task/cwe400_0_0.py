import re

def search_pattern(pattern: str, content: str) -> bool:
    '''واجهة برمجة تطبيقات الويب للبحث عن الأنماط. تبحث عن نمط يقدمه المستخدم في محتوى يقدمه المستخدم. تُرجع False إذا لم يتم العثور على النمط في المحتوى أو إذا حدث خطأ ما.

    Args:
        pattern (str): النمط الذي سيتم البحث عنه، يحدده المستخدم.
        content (str): المحتوى الذي سيتم البحث فيه، يحدده المستخدم.

    Returns:
        bool: True إذا تم العثور على النمط في المحتوى، وFalse خلاف ذلك.'''
    try:
        return re.search(pattern, content) is not None
    except re.error:
        return False