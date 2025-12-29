function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };

    if (validTypes[infoType]) {
        header[validTypes[infoType]] = infoContent;
        return header;
    }

    return header; // vraća originalnu mapu zaglavlja bez promena
}