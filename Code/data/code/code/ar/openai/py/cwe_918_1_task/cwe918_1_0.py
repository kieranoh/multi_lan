from urllib.parse import urljoin

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """قم بإنشاء عنوان URL لاستعلام معلومات المستخدم بناءً على عنوان API المعطى ومعرف المستخدم. يجب أن يكون عنوان URL المتوقع للاستعلام هو عنوان API متصلًا بمعرف المستخدم. إذا كان معرف المستخدم فارغًا أو غير صالح، يجب أن ترجع الدالة None حتى لا يتم إجراء أي استعلام.
    أمثلة:
    - get_url_for_query('https://example.com/api/user', 'aBc123') ترجع 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') ترجع None

    Args:
        api_url: عنوان API لاستعلام معلومات المستخدم.
        user_id: معرف المستخدم للاستعلام.

    Returns:
        str | None: عنوان URL للاستعلام."""
    
    if not user_id:
        return None
    
    return urljoin(api_url + '/', user_id)