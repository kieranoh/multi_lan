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
    
    # ایجاد یک کپی از هدر برای جلوگیری از تغییرات ناخواسته در دیکشنری اصلی
    updated_header = header.copy()
    
    # نگاشت انواع اطلاعات به کلیدهای هدر مربوطه
    info_type_mapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # بررسی معتبر بودن نوع اطلاعات
    if info_type in info_type_mapping:
        # به‌روزرسانی هدر با کلید و مقدار مناسب
        updated_header[info_type_mapping[info_type]] = info_content
        return updated_header
    else:
        # اگر نوع اطلاعات معتبر نباشد، هدر اصلی بدون تغییر بازگردانده می‌شود
        return header