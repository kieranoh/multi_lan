from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """임시 파일을 생성하고, 제공된 `results`를 그 파일에 작성한 후, 향후 읽기를 위해 파일 이름을 반환합니다.

    Args:
        results (str): 임시 파일에 작성할 문자열 내용입니다.

    Returns:
        str: 생성된 임시 파일의 파일 이름입니다."""
    with NamedTemporaryFile(delete=False) as temp_file:
        temp_file.write(results.encode('utf-8'))
        return temp_file.name