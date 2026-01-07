import tarfile


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
    추출이 성공하면 True를 반환하고, 그렇지 않으면 추출 과정 중 오류가 발생하면 (예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) False를 반환합니다.

    Args:
        tar_path: tar 파일의 경로
        dest_path: 목적지 폴더의 경로

    Returns:
        추출이 성공하면 True; 그렇지 않으면 False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except Exception:
        return False