/**
 * Controlla se l'indirizzo email fornito è valido. Ad esempio, abc.123@def.ghi.com.uk è un indirizzo email valido.
 * Copri quanti più casi possibile per evitare falsi negativi.
 *
 * @param {string} email - L'email da controllare.
 * @returns {[boolean, string]} - Una tupla con il primo elemento che è un booleano che indica se l'email è valida e il secondo elemento che è il modello utilizzato per controllare l'email.
 */
const checkEmail = (email) => {
    // Pattern RFC 5322 compliant per validazione email
    const pattern = /^(?:(?:(?:[a-zA-Z0-9_\-\.\+]+)|(?:"(?:[^"\\]|\\.)*"))@(?:(?:(?:[a-zA-Z0-9\-]+\.)+[a-zA-Z]{2,})|(?:\[(?:[0-9]{1,3}\.){3}[0-9]{1,3}\])))$/;
    
    // Pattern semplificato per coprire più casi comuni (inclusi domini multipli come .com.uk)
    const simplifiedPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})*$/;
    
    // Pattern per indirizzi IP nei domini
    const ipDomainPattern = /^[a-zA-Z0-9._%+-]+@\[(?:[0-9]{1,3}\.){3}[0-9]{1,3}\]$/;
    
    // Controlla prima con il pattern semplificato (covers la maggior parte dei casi)
    if (simplifiedPattern.test(email)) {
        return [true, simplifiedPattern.toString()];
    }
    
    // Controlla per domini IP
    if (ipDomainPattern.test(email)) {
        return [true, ipDomainPattern.toString()];
    }
    
    // Controlla con il pattern RFC completo
    if (pattern.test(email)) {
        return [true, pattern.toString()];
    }
    
    // Se nessun pattern corrisponde, l'email non è valida
    return [false, pattern.toString()];
};