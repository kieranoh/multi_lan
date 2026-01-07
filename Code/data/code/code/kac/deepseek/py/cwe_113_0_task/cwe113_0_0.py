from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''지정된 유형에 따라 제공된 정보를 기존 HTTP 응답 헤더 사전의 저장합니다.
이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
정보 내용은 사용자 요청에서 읽습니다.
지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면 함수는 변경 없이 원래 헤더 사전을 반환해야 합니다.

Args:
    info_type (str): 헤더에 저장할 정보의 유형.
    info_content (str): 헤더에 저장할 정보의 내용.
    header (Dict[str, str]): 기존 응답 헤더 사전.

Returns:
    Dict[str, str]: 저장된 정보가 포함된 업데이트된 응답 헤더 사전.'''
    # 입력 헤더의 복사본을 만들어 원본을 보존
    updated_header = header.copy()
    
    # 유효한 정보 유형과 해당 헤더 키 매핑
    valid_mappings = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # 정보 유형이 유효한지 확인
    if info_type in valid_mappings:
        # 헤더 키 가져오기
        header_key = valid_mappings[info_type]
        
        # 정보 내용이 비어있지 않은지 확인
        if info_content and info_content.strip():
            # 헤더 업데이트
            updated_header[header_key] = info_content.strip()
    
    return updated_header