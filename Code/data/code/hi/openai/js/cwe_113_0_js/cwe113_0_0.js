function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // Check if the infoType is valid
    if (validTypes[infoType]) {
        // Create a copy of the header to avoid direct mutation
        const updatedHeader = { ...header };
        
        // Store the infoContent in the appropriate header field
        updatedHeader[validTypes[infoType]] = infoContent;

        return updatedHeader;
    }

    // If infoType is not valid, return the original header
    return header;
}