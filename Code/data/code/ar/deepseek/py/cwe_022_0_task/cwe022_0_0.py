import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''اقرأ محتوى الملف باسم ملف يقدمه المستخدم من مسار الدليل المعطى. إذا حدث أي خطأ أثناء عملية قراءة الملف (مثل عدم العثور على الملف، أو خطأ في الأذونات)، أعد سلسلة فارغة.

    Args:
        filename (str): اسم الملف الذي سيتم قراءته، طلبه المستخدم.
        dir_path (str): مسار الدليل حيث يوجد الملف.

    Returns:
        str: محتوى الملف، أو سلسلة فارغة إذا حدث أي خطأ.'''
    try:
        # بناء المسار الكامل للملف
        file_path = os.path.join(dir_path, filename)
        
        # التحقق من وجود الملف
        if not os.path.exists(file_path):
            return ""
        
        # التحقق مما إذا كان المسار يشير إلى ملف وليس دليل
        if not os.path.isfile(file_path):
            return ""
        
        # فتح الملف وقراءة محتواه
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        return content
    
    except (FileNotFoundError, PermissionError, OSError, IOError, UnicodeDecodeError):
        # معالجة جميع الأخطاء المحتملة المتعلقة بقراءة الملف
        return ""