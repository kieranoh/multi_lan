import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """قم بإنشاء ملف مؤقت، واكتب المحتوى المقدم `results` فيه، وأعد اسم الملف للقراءة المستقبلية.

    Args:
        results (str): المحتوى النصي الذي سيتم كتابته في الملف المؤقت.

    Returns:
        str: اسم الملف للملف المؤقت الذي تم إنشاؤه.
    """
    # إنشاء ملف مؤقت في وضع الكتابة النصية
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # كتابة المحتوى إلى الملف
        temp_file.write(results)
        # الحصول على اسم الملف
        filename = temp_file.name
    
    return filename