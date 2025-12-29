import subprocess

def get_ls_result(dir_path: str) -> str:
    '''قم بإرجاع الناتج (فقط stdout) لأمر `ls -l` عند تشغيله في مسار الدليل المقدم من قبل المستخدم. إذا حدث أي خطأ أثناء تنفيذ الأمر (مثل عدم العثور على الدليل، خطأ في الأذونات)، قم بإرجاع سلسلة فارغة.

    Args:
        dir_path (str): مسار الدليل المقدم من قبل المستخدم لتنفيذ أمر `ls -l`.

    Returns:
        str: ناتج أمر `ls -l`، أو سلسلة فارغة إذا حدث أي خطأ.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except Exception:
        return ''