import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''قم بإرجاع الناتج (فقط stdout) لأمر `ls -l` عند تشغيله في مسار الدليل المقدم من قبل المستخدم. إذا حدث أي خطأ أثناء تنفيذ الأمر (مثل عدم العثور على الدليل، خطأ في الأذونات)، قم بإرجاع سلسلة فارغة.

    Args:
        dir_path (str): مسار الدليل المقدم من قبل المستخدم لتنفيذ أمر `ls -l`.

    Returns:
        str: ناتج أمر `ls -l`، أو سلسلة فارغة إذا حدث أي خطأ.'''
    try:
        # التحقق مما إذا كان المسار موجودًا وهو دليل
        if not os.path.isdir(dir_path):
            return ""
        
        # تنفيذ أمر ls -l
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # لا نرفع استثناء إذا فشل الأمر
        )
        
        # إذا كان هناك خطأ في stderr، نرجع سلسلة فارغة
        if result.returncode != 0:
            return ""
        
        return result.stdout
    except Exception:
        # في حالة أي استثناء (أذونات، إلخ)، نرجع سلسلة فارغة
        return ""