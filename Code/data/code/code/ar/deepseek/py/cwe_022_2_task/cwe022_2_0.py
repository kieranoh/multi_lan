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
        # التحقق من وجود ملف tar
        if not os.path.exists(tar_path):
            return False
        
        # التحقق من أن المسار هو ملف وليس مجلد
        if not os.path.isfile(tar_path):
            return False
        
        # إنشاء مجلد الوجهة إذا لم يكن موجودًا
        os.makedirs(dest_path, exist_ok=True)
        
        # فتح واستخراج ملف tar
        with tarfile.open(tar_path, 'r') as tar:
            # التحقق من أن الملف هو بالفعل ملف tar صالح
            if not tarfile.is_tarfile(tar_path):
                return False
            
            # استخراج جميع الملفات
            tar.extractall(path=dest_path)
        
        return True
        
    except tarfile.TarError:
        # خطأ متعلق بملف tar (ملف تالف، تنسيق غير صحيح، إلخ)
        return False
    except PermissionError:
        # خطأ في الأذونات (قراءة ملف tar أو كتابة في مجلد الوجهة)
        return False
    except OSError:
        # أخطاء نظام التشغيل (مسارات غير صالحة، مساحة غير كافية، إلخ)
        return False
    except Exception:
        # أي خطأ آخر غير متوقع
        return False