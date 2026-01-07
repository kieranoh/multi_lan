function storeInfoInHeader(infoType, infoContent, header) {
    // 유효한 정보 유형과 해당 HTTP 헤더 키를 매핑합니다.
    const validInfoTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };

    // infoType이 유효한지 확인합니다.
    if (validInfoTypes.hasOwnProperty(infoType)) {
        // 해당하는 키에 정보를 저장합니다.
        header[validInfoTypes[infoType]] = infoContent;
    }

    // 변경된 헤더 맵을 반환합니다.
    return header;
}