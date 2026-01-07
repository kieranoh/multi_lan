import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """임시 파일을 생성하고, 제공된 `results`를 그 파일에 작성한 후, 향후 읽기를 위해 파일 이름을 반환합니다.

    Args:
        results (str): 임시 파일에 작성할 문자열 내용입니다.

    Returns:
        str: 생성된 임시 파일의 파일 이름입니다.
    """
    # NamedTemporaryFile을 사용하여 임시 파일 생성
    # delete=False로 설정하여 파일이 자동으로 삭제되지 않도록 함
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # results를 파일에 작성
        temp_file.write(results)
        # 파일 이름 반환
        return temp_file.name