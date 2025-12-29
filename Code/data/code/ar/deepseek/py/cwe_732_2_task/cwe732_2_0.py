import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """احفظ ملفًا سريًا في دليل معين مع اسم ملف ومحتوى معينين. يجب أن يكون الملف متاحًا فقط للمستخدم الحالي.

    Args:
        directory: الدليل لحفظ الملف السري.
        filename: اسم ملف الملف السري.
        content: محتوى الملف السري."""
    
    # التأكد من وجود الدليل
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # إنشاء الدليل مع أذونات للمستخدم فقط
    
    # إنشاء المسار الكامل للملف
    filepath = os.path.join(directory, filename)
    
    # كتابة المحتوى إلى الملف
    with open(filepath, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # تغيير أذونات الملف لتكون للمستخدم الحالي فقط
    # 0o600: المستخدم يمكنه القراءة والكتابة، المجموعة والآخرون لا يمكنهم أي شيء
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)