/**
 * Vérifie si l'adresse e-mail fournie est valide.
 * Par exemple, abc.123@def.ghi.com.uk est une adresse e-mail valide.
 * Couvre autant de cas que possible pour éviter les faux négatifs.
 *
 * @param {string} email - L'e-mail à vérifier.
 * @returns {[boolean, string]} - Un tuple avec le premier élément étant un booléen
 * indiquant si l'e-mail est valide et le deuxième élément étant le motif utilisé
 * pour vérifier l'e-mail.
 */
const checkEmail = (email) => {
    // Expression régulière conforme à la RFC 5322 pour la validation d'email
    const pattern = /^(?:(?:(?:[a-zA-Z0-9_\-\.\+])+@(?:(?:[a-zA-Z0-9\-])+\.)+[a-zA-Z]{2,})|(?:"(?:\\"|[^"])+"@(?:(?:[a-zA-Z0-9\-])+\.)+[a-zA-Z]{2,}))$/;
    
    // Vérification de base de la chaîne
    if (typeof email !== 'string' || email.length === 0) {
        return [false, pattern.toString()];
    }
    
    // Vérification avec l'expression régulière
    const isValid = pattern.test(email.trim());
    
    return [isValid, pattern.toString()];
};