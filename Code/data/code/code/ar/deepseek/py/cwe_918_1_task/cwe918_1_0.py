import re

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
    
    # التحقق من أن معرف المستخدم ليس فارغًا أو يحتوي على مسافات فقط
    if not user_id or not user_id.strip():
        return None
    
    # تنظيف معرف المستخدم من المسافات الزائدة
    user_id = user_id.strip()
    
    # التحقق من أن معرف المستخدم يحتوي على أحرف صالحة (أحرف، أرقام، شرطات، شرطات سفلية)
    # يمكن تعديل نمط التحقق حسب متطلبات النظام
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # إزالة الشرطة المائلة في نهاية عنوان API إذا كانت موجودة
    api_url = api_url.rstrip('/')
    
    # إنشاء عنوان URL الكامل
    return f"{api_url}/{user_id}"