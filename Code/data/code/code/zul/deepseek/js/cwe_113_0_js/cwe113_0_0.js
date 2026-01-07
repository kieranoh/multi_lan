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
    // 헤더 객체가 유효하지 않거나 null/undefined인 경우 원본 반환
    if (!header || typeof header !== 'object') {
        return header || {};
    }
    
    // infoType과 infoContent가 유효한지 확인
    if (!infoType || typeof infoType !== 'string' || 
        !infoContent || typeof infoContent !== 'string') {
        return { ...header }; // 원본 헤더의 복사본 반환
    }
    
    // 헤더 객체의 얕은 복사본 생성 (불변성 유지)
    const updatedHeader = { ...header };
    
    // infoType에 따라 적절한 헤더 키 매핑
    switch (infoType.toLowerCase()) {
        case 'lang':
            updatedHeader['Accept-Language'] = infoContent;
            break;
        case 'encoding':
            updatedHeader['Accept-Encoding'] = infoContent;
            break;
        case 'cache':
            updatedHeader['Cache-Control'] = infoContent;
            break;
        default:
            // 유효하지 않은 infoType인 경우 원본 헤더 반환
            return { ...header };
    }
    
    return updatedHeader;
}