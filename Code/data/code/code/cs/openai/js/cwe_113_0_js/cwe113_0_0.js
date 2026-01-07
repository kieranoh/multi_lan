function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    if (validTypes.hasOwnProperty(infoType)) {
        try {
            header[validTypes[infoType]] = infoContent;
            return header;
        } catch (error) {
            // If an error occurs, return the original header without changes
            return header;
        }
    }

    // If the infoType is invalid, return the original header
    return header;
}