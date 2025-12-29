from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """قم بإنشاء ملف مؤقت، واكتب المحتوى المقدم `results` فيه، وأعد اسم الملف للقراءة المستقبلية.

    Args:
        results (str): المحتوى النصي الذي سيتم كتابته في الملف المؤقت.

    Returns:
        str: اسم الملف للملف المؤقت الذي تم إنشاؤه."""
    
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name