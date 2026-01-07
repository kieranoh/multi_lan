function storeInfoInHeader(infoType, infoContent, header) {
    // 입력 유효성 검사
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || 
        !header || typeof header !== 'object') {
        return header;
    }
    
    // 헤더 객체의 불변성을 보장하기 위해 복사본 생성
    const updatedHeader = { ...header };
    
    // infoType에 따라 적절한 헤더 키로 변환
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
            return header;
    }
    
    return updatedHeader;
}