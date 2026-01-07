/**
 * Egin egiaztatu emandako posta elektronikoa baliozkoa den.
 * @param {string} email - Egiaztatu beharreko posta elektronikoa.
 * @returns {boolean} - true baliozkoa bada, false bestela.
 */
const checkEmail = (email) => {
    // Lehenik, sarrera string bat dela eta hutsik ez dagoela egiaztatu
    if (typeof email !== 'string' || email.trim() === '') {
        return false;
    }
    
    const trimmedEmail = email.trim();
    
    // Posta elektronikoaren oinarrizko egitura egiaztatu: local-part@domain
    const atSymbolCount = (trimmedEmail.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return false;
    }
    
    const [localPart, domain] = trimmedEmail.split('@');
    
    // Local-part eta domain hutsik ez daudela egiaztatu
    if (!localPart || !domain) {
        return false;
    }
    
    // Local-part-aren luzera egiaztatu (RFC 5321: gehienez 64 karaktere)
    if (localPart.length > 64) {
        return false;
    }
    
    // Domain-aren luzera egiaztatu (RFC 1035: gehienez 255 karaktere)
    if (domain.length > 255) {
        return false;
    }
    
    // Domain-ak gutxienez puntu bat izan behar du
    if (!domain.includes('.')) {
        return false;
    }
    
    // Domain-aren azken zatia (TLD) gutxienez 2 karaktere izan behar ditu
    const domainParts = domain.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return false;
    }
    
    // Karaktere baliogabeak egiaztatu
    const invalidCharsRegex = /[<>()\[\]\\,;:"\s]/;
    if (invalidCharsRegex.test(localPart) || invalidCharsRegex.test(domain)) {
        return false;
    }
    
    // Puntu jarraituak egiaztatu
    if (localPart.includes('..') || domain.includes('..')) {
        return false;
    }
    
    // Local-part edo domain puntu batekin hasten edo amaitzen bada
    if (localPart.startsWith('.') || localPart.endsWith('.') || 
        domain.startsWith('.') || domain.endsWith('.')) {
        return false;
    }
    
    // Karaktere guztiak ASCII direla egiaztatu (sinplifikazioa)
    const nonAsciiRegex = /[^\x00-\x7F]/;
    if (nonAsciiRegex.test(trimmedEmail)) {
        return false;
    }
    
    // Azken egiaztapena: erregex sinple bat erabili formatu egokia duela egiaztatzeko
    const emailRegex = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    return emailRegex.test(trimmedEmail);
};