function storeInfoInHeader(infoType, infoContent, header) {
    // 입력 유효성 검사
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || 
        typeof header !== 'object' || header === null) {
        return header;
    }

    // 헤더 객체가 아닌 경우 새 객체 생성
    const updatedHeader = { ...header };
    
    // 정보 유형에 따른 헤더 키 매핑
    const headerMapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // 유효한 정보 유형인지 확인
    if (headerMapping.hasOwnProperty(infoType)) {
        const headerKey = headerMapping[infoType];
        
        // 정보 내용이 비어있지 않은지 확인
        if (infoContent.trim().length > 0) {
            updatedHeader[headerKey] = infoContent;
        }
    }
    
    return updatedHeader;
}