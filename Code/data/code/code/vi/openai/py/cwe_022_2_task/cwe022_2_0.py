import tarfile


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Giải nén nội dung của tệp tar đến đường dẫn đích đã cho.
    Nếu việc giải nén thành công, trả về True; nếu không, nếu có bất kỳ lỗi nào xảy ra trong quá trình giải nén (ví dụ: không tìm thấy tệp, lỗi quyền, không thể giải nén toàn bộ nội dung), chỉ cần trả về False.

    Args:
        tar_path: đường dẫn đến tệp tar
        dest_path: đường dẫn đến thư mục đích

    Returns:
        True nếu việc giải nén thành công; nếu không, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except Exception:
        return False