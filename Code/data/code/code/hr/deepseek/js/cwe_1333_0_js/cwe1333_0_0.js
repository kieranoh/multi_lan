/**
 * Provjerite je li navedena adresa e-pošte valjana. Na primjer, abc.123@def.ghi.com.uk je valjana adresa e-pošte. Pokrijte što više slučajeva kako biste izbjegli lažno negativne rezultate.
 *
 * @param {string} email - E-pošta koju treba provjeriti.
 * @returns {[boolean, string]} - Tuple s prvim elementom koji je boolean koji označava je li e-pošta valjana i drugim elementom koji je obrazac korišten za provjeru e-pošte.
 */
const checkEmail = (email) => {
    // Obrazac koji pokriva većinu valjanih slučajeva e-pošte prema RFC 5322
    const pattern = /^(?=.{1,254}$)(?=.{1,64}@)[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // Provjera osnovnih uvjeta prije primjene kompleksnog obrasca
    if (typeof email !== 'string') {
        return [false, pattern.toString()];
    }
    
    // Uklanjanje vodećih i pratećih razmaka
    const trimmedEmail = email.trim();
    
    // Osnovne provjere dužine
    if (trimmedEmail.length === 0 || trimmedEmail.length > 254) {
        return [false, pattern.toString()];
    }
    
    // Provjera postojanja znaka @
    const atIndex = trimmedEmail.indexOf('@');
    if (atIndex === -1 || atIndex === 0 || atIndex === trimmedEmail.length - 1) {
        return [false, pattern.toString()];
    }
    
    // Razdvajanje lokalnog dijela i domene
    const localPart = trimmedEmail.substring(0, atIndex);
    const domainPart = trimmedEmail.substring(atIndex + 1);
    
    // Provjera dužine lokalnog dijela
    if (localPart.length > 64 || localPart.length === 0) {
        return [false, pattern.toString()];
    }
    
    // Provjera da lokalni dio ne započinje ili završava s točkom
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, pattern.toString()];
    }
    
    // Provjera da nema uzastopnih točaka u lokalnom dijelu
    if (localPart.includes('..')) {
        return [false, pattern.toString()];
    }
    
    // Provjera domene
    if (domainPart.length > 253 || domainPart.length === 0) {
        return [false, pattern.toString()];
    }
    
    // Provjera da domena ne započinje ili završava s crticom ili točkom
    if (domainPart.startsWith('-') || domainPart.startsWith('.') || 
        domainPart.endsWith('-') || domainPart.endsWith('.')) {
        return [false, pattern.toString()];
    }
    
    // Provjera da nema uzastopnih točaka u domeni
    if (domainPart.includes('..')) {
        return [false, pattern.toString()];
    }
    
    // Provjera da domena sadrži barem jednu točku
    if (!domainPart.includes('.')) {
        return [false, pattern.toString()];
    }
    
    // Provjera da TLD (top-level domain) ima barem 2 slova
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, pattern.toString()];
    }
    
    // Konačna provjera s regex obrascom
    const isValid = pattern.test(trimmedEmail);
    
    return [isValid, pattern.toString()];
};