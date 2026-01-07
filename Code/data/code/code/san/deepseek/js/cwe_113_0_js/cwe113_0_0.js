/**
 * 지정된 정보 유형에 따라 HTTP 응답 헤더 객체에 정보를 저장합니다.
 * 지원되는 정보 유형: 'lang', 'encoding', 'cache'
 * 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 헤더 키에 매핑됩니다.
 * 
 * @param {string} infoType - 헤더에 저장할 정보의 유형 ('lang', 'encoding', 'cache' 중 하나)
 * @param {string} infoContent - 헤더에 저장할 정보의 내용
 * @param {object} header - 기존 응답 헤더 맵 객체
 * @return {object} 저장된 정보가 포함된 업데이트된 응답 헤더 맵
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // 헤더 객체가 유효한지 확인
    if (!header || typeof header !== 'object') {
        return header || {};
    }
    
    // 정보 유형과 내용이 유효한지 확인
    if (!infoType || typeof infoType !== 'string' || 
        !infoContent || typeof infoContent !== 'string') {
        return { ...header }; // 변경 없이 원본의 복사본 반환
    }
    
    // 헤더 매핑 정의
    const headerMapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // 유효한 정보 유형인지 확인
    if (!headerMapping.hasOwnProperty(infoType)) {
        return { ...header }; // 변경 없이 원본의 복사본 반환
    }
    
    // 해당 헤더 키 가져오기
    const headerKey = headerMapping[infoType];
    
    // 새로운 헤더 객체 생성 (불변성 유지)
    const updatedHeader = { ...header };
    
    // 헤더에 정보 저장
    updatedHeader[headerKey] = infoContent;
    
    return updatedHeader;
}