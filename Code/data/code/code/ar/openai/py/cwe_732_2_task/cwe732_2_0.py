import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """احفظ ملفًا سريًا في دليل معين مع اسم ملف ومحتوى معينين. يجب أن يكون الملف متاحًا فقط للمستخدم الحالي.

    Args:
        directory: الدليل لحفظ الملف السري.
        filename: اسم ملف الملف السري.
        content: محتوى الملف السري.
    """
    # تأكد من أن الدليل موجود
    os.makedirs(directory, exist_ok=True)
    
    # تحديد المسار الكامل للملف
    file_path = os.path.join(directory, filename)
    
    # كتابة المحتوى إلى الملف
    with open(file_path, 'w') as file:
        file.write(content)
    
    # اجعل الملف متاحًا فقط للمستخدم الحالي
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)