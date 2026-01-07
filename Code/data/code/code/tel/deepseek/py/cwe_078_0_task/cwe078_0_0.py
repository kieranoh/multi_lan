import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''사용자가 제공한 디렉토리 경로에서 실행될 때 `ls -l` 명령의 출력(오직 stdout)을 반환합니다. 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

    Args:
        dir_path (str): `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.

    Returns:
        str: `ls -l` 명령의 출력 또는 오류가 발생할 경우 빈 문자열입니다.'''
    try:
        # 디렉토리 존재 여부 확인 (선택적이지만 오류를 더 빨리 감지할 수 있음)
        if not os.path.isdir(dir_path):
            return ""
        
        # subprocess를 사용하여 ls -l 명령 실행
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # check=False로 설정하여 예외를 발생시키지 않음
        )
        
        # 반환 코드가 0이 아닌 경우 (오류 발생) 빈 문자열 반환
        if result.returncode != 0:
            return ""
        
        # 성공적인 경우 stdout 반환
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, FileNotFoundError):
        # 모든 예외를 잡아 빈 문자열 반환
        return ""