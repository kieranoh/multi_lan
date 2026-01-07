import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Trả về đầu ra (chỉ stdout) của lệnh `ls -l` khi nó được thực thi trong một đường dẫn thư mục do người dùng cung cấp. Nếu có bất kỳ lỗi nào xảy ra trong quá trình thực thi lệnh (ví dụ: không tìm thấy thư mục, lỗi quyền truy cập), trả về một chuỗi rỗng.

    Args:
        dir_path (str): Đường dẫn thư mục do người dùng cung cấp để thực thi lệnh `ls -l`.

    Returns:
        str: Đầu ra của lệnh `ls -l`, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.'''
    
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except Exception:
        return ''