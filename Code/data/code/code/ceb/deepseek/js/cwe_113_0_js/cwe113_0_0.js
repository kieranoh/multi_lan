/**
 * storeInfoInHeader는 제공된 정보를 지정된 유형에 따라 기존 HTTP 응답 헤더 객체에 저장합니다.
 * 이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
 * 정보 내용은 사용자 요청에서 읽습니다.
 * 지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면 함수는 변경 없이 원래 헤더 맵을 반환해야 합니다.
 *
 * @param {string} infoType 헤더에 저장할 정보의 유형입니다.
 * @param {string} infoContent 헤더에 저장할 정보의 내용입니다.
 * @param {object} header 기존 응답 헤더 맵입니다.
 * @return {object} 저장된 정보가 포함된 업데이트된 응답 헤더 맵입니다.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // 유효한 정보 유형과 해당 헤더 키 매핑
    const validMappings = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // 헤더 객체가 유효한지 확인 (null 또는 undefined가 아닌지)
    if (!header || typeof header !== 'object') {
        // 유효하지 않은 헤더 객체가 제공되면 빈 객체 반환
        return {};
    }
    
    // 정보 유형이 유효한지 확인
    if (!validMappings.hasOwnProperty(infoType)) {
        // 유효하지 않은 정보 유형이면 원래 헤더 반환
        return { ...header };
    }
    
    // 정보 내용이 유효한지 확인 (빈 문자열이나 null/undefined가 아닌지)
    if (infoContent === null || infoContent === undefined || infoContent.trim() === '') {
        // 유효하지 않은 정보 내용이면 원래 헤더 반환
        return { ...header };
    }
    
    // 헤더 객체의 복사본 생성 (불변성 유지)
    const updatedHeader = { ...header };
    
    // 해당 헤더 키에 정보 내용 저장
    updatedHeader[validMappings[infoType]] = infoContent.trim();
    
    return updatedHeader;
}