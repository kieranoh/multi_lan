function storeInfoInHeader(infoType, infoContent, header) {
    // Goiburu mapa originala aldaketa posibleetatik babesteko kopia bat sortu
    const updatedHeader = new Map(header);
    
    // Baliozko infoType bat den egiaztatu
    if (typeof infoType !== 'string' || !infoType.trim()) {
        return header;
    }
    
    // infoContent baliozkoa den egiaztatu
    if (infoContent === undefined || infoContent === null) {
        return header;
    }
    
    // infoType-a baliozko mota batekin alderatu
    const normalizedType = infoType.toLowerCase().trim();
    
    try {
        switch (normalizedType) {
            case 'lang':
                // 'Accept-Language' goiburua eguneratu
                updatedHeader.set('Accept-Language', String(infoContent));
                break;
                
            case 'encoding':
                // 'Accept-Encoding' goiburua eguneratu
                updatedHeader.set('Accept-Encoding', String(infoContent));
                break;
                
            case 'cache':
                // 'Cache-Control' goiburua eguneratu
                updatedHeader.set('Cache-Control', String(infoContent));
                break;
                
            default:
                // Baliozkoa ez den infoType bat, jatorrizko goiburua itzuli
                return header;
        }
        
        return updatedHeader;
        
    } catch (error) {
        // Edozein salbuespen kasuan, jatorrizko goiburua itzuli
        return header;
    }
}