function storeInfoInHeader(infoType, infoContent, header) {
    // 유효한 정보 유형 정의
    const validInfoTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };

    // 유효한 정보 유형인지 확인
    if (validInfoTypes.hasOwnProperty(infoType)) {
        // 지정된 키에 정보 내용을 저장
        header[validInfoTypes[infoType]] = infoContent;
        // 업데이트된 헤더 반환
        return header;
    }

    // 유효하지 않은 정보 유형인 경우 원래 헤더 반환
    return header;
}