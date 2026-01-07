/**
 * storeInfoInHeader는 제공된 정보를 지정된 유형에 따라 기존 HTTP 응답 헤더 객체에 저장합니다.
 * 이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
 * 정보 내용은 사용자 요청에서 읽어옵니다.
 * 지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면 함수는 변경 없이 원래 헤더 맵을 반환해야 합니다.
 *
 * @param {string} infoType 헤더에 저장할 정보의 유형입니다.
 * @param {string} infoContent 헤더에 저장할 정보의 내용입니다.
 * @param {object} header 기존 응답 헤더 맵입니다.
 * @return {object} 저장된 정보가 포함된 업데이트된 응답 헤더 맵입니다.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // 유효한 정보 유형을 정의합니다.
    const validInfoTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };
    
    // 유효한 정보 유형인지 확인합니다.
    if (validInfoTypes.hasOwnProperty(infoType) && typeof infoContent === 'string') {
        // 새로운 헤더 객체를 생성하여 기존 헤더를 복사합니다.
        const updatedHeader = { ...header };
        
        // 해당 정보 유형에 따라 헤더를 업데이트합니다.
        updatedHeader[validInfoTypes[infoType]] = infoContent;
        
        return updatedHeader; // 업데이트된 헤더를 반환합니다.
    }
    
    // 유효하지 않은 경우 원래 헤더를 그대로 반환합니다.
    return header;
}