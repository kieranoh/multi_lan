function storeInfoInHeader(infoType, infoContent, header) {
    // 유효한 정보 유형을 정의합니다.
    const validTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };

    // 제공된 정보 유형이 유효한 경우에만 헤더를 업데이트합니다.
    if (validTypes.hasOwnProperty(infoType)) {
        header[validTypes[infoType]] = infoContent;
    }

    // 업데이트된 헤더를 반환합니다.
    return header;
}