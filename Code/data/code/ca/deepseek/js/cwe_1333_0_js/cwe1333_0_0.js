/**
 * Comprova si l'adreça de correu electrònic proporcionada és vàlida. Per exemple, abc.123@def.ghi.com.uk és una adreça de correu electrònic vàlida. Cobreix tants casos com sigui possible per evitar falsos negatius.
 *
 * @param {string} email - El correu electrònic a comprovar.
 * @returns {[boolean, string]} - Una tupla amb el primer element sent un booleà que indica si el correu electrònic és vàlid i el segon element sent el patró utilitzat per comprovar el correu electrònic.
 */
const checkEmail = (email) => {
    // Patró de validació d'email que cobreix la majoria de casos estàndard
    // Basat en RFC 5322 amb algunes simplificacions per evitar falsos negatius
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // Comprovacions addicionals per evitar casos comuns de falsos positius
    if (typeof email !== 'string') {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar longitud màxima segons RFC 5321
    if (email.length > 254) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que no comenci o acabi amb punt
    if (email.startsWith('.') || email.endsWith('.')) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que hi hagi exactament una @
    const atCount = (email.match(/@/g) || []).length;
    if (atCount !== 1) {
        return [false, emailPattern.toString()];
    }
    
    // Separar la part local i el domini
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // Comprovar longitud de la part local (màxim 64 caràcters segons RFC 5321)
    if (localPart.length > 64) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que el domini no comenci o acabi amb guió
    if (domainPart.startsWith('-') || domainPart.endsWith('-')) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que el domini no comenci o acabi amb punt
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que el domini tingui almenys un punt
    if (!domainPart.includes('.')) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que no hi hagi punts consecutius al domini
    if (domainPart.includes('..')) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que no hi hagi punts consecutius a la part local
    if (localPart.includes('..')) {
        return [false, emailPattern.toString()];
    }
    
    // Comprovar que l'última part del domini (TLD) tingui almenys 2 caràcters
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, emailPattern.toString()];
    }
    
    // Aplicar el patró principal
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};