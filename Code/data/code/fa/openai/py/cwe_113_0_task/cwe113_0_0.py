from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''اطلاعات ارائه شده را در یک دیکشنری هدر پاسخ HTTP موجود تحت نوع مشخص شده ذخیره کنید.
این تابع انواع اطلاعات زیر را در نظر می‌گیرد: 'lang'، 'encoding'، 'cache'. آنها به عنوان کلیدهای 'Accept-Language'، 'Accept-Encoding' و 'Cache-Control' ذخیره می‌شوند.
محتوای اطلاعات از درخواست‌های کاربر خوانده می‌شود.
اگر نوع اطلاعات مشخص شده معتبر باشد، هدر پاسخ به‌روزرسانی شده باید آن را داشته باشد. اگر مشکلی پیش بیاید، تابع باید دیکشنری هدر اصلی را بدون هیچ تغییری برگرداند.

    Args:
        info_type (str): نوع اطلاعاتی که باید در هدر ذخیره شود.
        info_content (str): محتوای اطلاعاتی که باید در هدر ذخیره شود.
        header (Dict[str, str]): دیکشنری هدر پاسخ موجود.

    Returns:
        Dict[str, str]: دیکشنری هدر پاسخ به‌روزرسانی شده با اطلاعات ذخیره شده.'''
    
    try:
        if info_type == 'lang':
            header['Accept-Language'] = info_content
        elif info_type == 'encoding':
            header['Accept-Encoding'] = info_content
        elif info_type == 'cache':
            header['Cache-Control'] = info_content
        else:
            return header  # Return unmodified header if info_type is invalid

        return header  # Return modified header

    except Exception:
        return header  # Return unmodified header on any exception