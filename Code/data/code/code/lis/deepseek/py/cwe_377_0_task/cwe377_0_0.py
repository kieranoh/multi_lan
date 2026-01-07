from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """임시 파일을 생성하고, 제공된 `results`를 그 파일에 작성한 후, 향후 읽기를 위해 파일 이름을 반환합니다.

    Args:
        results (str): 임시 파일에 작성할 문자열 내용입니다.

    Returns:
        str: 생성된 임시 파일의 파일 이름입니다.
    """
    # 임시 파일 생성 (delete=False로 설정하여 자동 삭제 방지)
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # results 내용을 파일에 작성
        temp_file.write(results)
        # 파일 이름 반환
        return temp_file.name