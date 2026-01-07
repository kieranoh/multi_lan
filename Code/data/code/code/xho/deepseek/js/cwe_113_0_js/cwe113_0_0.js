function storeInfoInHeader(infoType, infoContent, header) {
    // Validate inputs
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || 
        typeof header !== 'object' || header === null) {
        return header;
    }
    
    // Create a copy of the header to avoid mutating the original
    const updatedHeader = { ...header };
    
    // Map infoType to corresponding header key
    const headerMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // Check if infoType is valid and get the header key
    const headerKey = headerMap[infoType];
    
    // If infoType is valid, store the infoContent in the header
    if (headerKey) {
        updatedHeader[headerKey] = infoContent;
    }
    
    return updatedHeader;
}