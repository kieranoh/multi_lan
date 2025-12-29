from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Tạo một tệp tạm thời, ghi `results` được cung cấp vào đó và trả về tên tệp để đọc sau này.

    Args:
        results (str): Nội dung chuỗi để ghi vào tệp tạm thời.

    Returns:
        str: Tên tệp của tệp tạm thời được tạo."""
    
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name