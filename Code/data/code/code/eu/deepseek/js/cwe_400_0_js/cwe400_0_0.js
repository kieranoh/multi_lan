function search_pattern(pattern, content) {
    // Egiaztatu sarrerak baliozkoak diren
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Hutsik dauden kasuak maneiatu
    if (pattern.length === 0 || content.length === 0) {
        return false;
    }
    
    try {
        // Patroia bilatu edukiaren barruan
        return content.includes(pattern);
    } catch (error) {
        // Errore bat gertatzen bada (adibidez, memoria arazoak), itzuli faltsua
        console.error('Errorea patroia bilatzean:', error);
        return false;
    }
}