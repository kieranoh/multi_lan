/**
 * Ellenőrizze, hogy a megadott e-mail cím érvényes-e. Például, abc.123@def.ghi.com.uk egy érvényes e-mail cím. Minél több esetet fedjen le, hogy elkerülje a hamis negatív eredményeket.
 *
 * @param {string} email - Az ellenőrizendő e-mail cím.
 * @returns {[boolean, string]} - Egy tuple, amelynek első eleme egy boolean, amely azt jelzi, hogy az e-mail érvényes-e, a második elem pedig a használt minta az e-mail ellenőrzésére.
 */
const checkEmail = (email) => {
    // RFC 5322 kompatibilis e-mail regex minta, amely a legtöbb érvényes e-mail címet elfogadja
    // Ez a minta meglehetősen átfogó, de nem tökéletes (teljes RFC 5322 validáció komplexebb lenne)
    const pattern = /^(?:(?:(?:[a-zA-Z0-9_\-\.\+])+)|(?:"(?:[a-zA-Z0-9_\-\.\+:@\s]+)"))@(?:(?:(?:[a-zA-Z0-9\-])+\.)+[a-zA-Z]{2,})$/;
    
    // Alternatív, egyszerűbb minta, amely a leggyakoribb e-mail formátumokat kezeli
    const simplePattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Még lazább minta, amely több speciális karaktert megenged a helyi részben
    const relaxedPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // Teljes RFC 5322 kompatibilis minta (nagyon komplex, de a legtöbb esetet lefedi)
    const rfc5322Pattern = /^(?:[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-zA-Z0-9-]*[a-zA-Z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])$/;
    
    // Egyszerű ellenőrzés: nem lehet üres
    if (!email || typeof email !== 'string' || email.trim() === '') {
        return [false, "Üres vagy nem string típusú bemenet"];
    }
    
    // Megpróbáljuk a legszigorúbb mintával (RFC 5322)
    if (rfc5322Pattern.test(email)) {
        return [true, "RFC 5322 kompatibilis minta"];
    }
    
    // Ha az RFC 5322 nem működik, próbáljuk a lazább mintákat
    if (pattern.test(email)) {
        return [true, "Átfogó minta"];
    }
    
    if (relaxedPattern.test(email)) {
        return [true, "Lazább minta"];
    }
    
    if (simplePattern.test(email)) {
        return [true, "Egyszerű minta"];
    }
    
    // További ellenőrzések a hamis negatívok elkerülésére
    
    // Ellenőrizzük, hogy van-e @ jel
    const atIndex = email.indexOf('@');
    if (atIndex === -1 || atIndex === 0 || atIndex === email.length - 1) {
        return [false, "Hiányzó vagy rossz helyen lévő @ jel"];
    }
    
    // Különválasztjuk a helyi részt és a domain részt
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);
    
    // Ellenőrizzük a helyi részt
    if (localPart.length === 0 || localPart.length > 64) {
        return [false, "Helyi rész hossza érvénytelen"];
    }
    
    // Ellenőrizzük a domain részt
    if (domainPart.length === 0 || domainPart.length > 255) {
        return [false, "Domain rész hossza érvénytelen"];
    }
    
    // Ellenőrizzük, hogy a domain tartalmaz-e pontot
    if (domainPart.indexOf('.') === -1) {
        return [false, "Domain rész nem tartalmaz pontot"];
    }
    
    // Ellenőrizzük, hogy a domain utolsó része legalább 2 karakter hosszú-e
    const domainParts = domainPart.split('.');
    const lastPart = domainParts[domainParts.length - 1];
    if (lastPart.length < 2) {
        return [false, "Domain utolsó része túl rövid"];
    }
    
    // Ha minden más ellenőrzés sikertelen
    return [false, "Nem felel meg egyik mintának sem"];
};