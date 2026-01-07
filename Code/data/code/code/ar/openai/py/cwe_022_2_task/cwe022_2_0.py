import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''قم باستخراج محتوى ملف tar إلى مسار الوجهة المحدد.
    إذا كانت عملية الاستخراج ناجحة، ارجع True؛ خلاف ذلك، إذا حدث أي خطأ أثناء عملية الاستخراج (مثل عدم العثور على الملف، خطأ في الأذونات، عدم القدرة على استخراج كل المحتوى)، ارجع فقط False.

    Args:
        tar_path: المسار إلى ملف tar
        dest_path: المسار إلى مجلد الوجهة

    Returns:
        True إذا كانت عملية الاستخراج ناجحة؛ خلاف ذلك، False'''
    
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False