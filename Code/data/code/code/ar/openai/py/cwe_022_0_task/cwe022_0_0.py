import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''اقرأ محتوى الملف باسم ملف يقدمه المستخدم من مسار الدليل المعطى. إذا حدث أي خطأ أثناء عملية قراءة الملف (مثل عدم العثور على الملف، أو خطأ في الأذونات)، أعد سلسلة فارغة.

    Args:
        filename (str): اسم الملف الذي سيتم قراءته، طلبه المستخدم.
        dir_path (str): مسار الدليل حيث يوجد الملف.

    Returns:
        str: محتوى الملف، أو سلسلة فارغة إذا حدث أي خطأ.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except (FileNotFoundError, PermissionError, IOError):
        return ''