function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    if (validTypes[infoType]) {
        header[validTypes[infoType]] = infoContent;
        return header;
    }

    return header; // Return the original header if infoType is invalid
}