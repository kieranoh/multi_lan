/**
 * Vérifiez si l'adresse e-mail fournie est valide. Par exemple, abc.123@def.ghi.com.uk est une adresse e-mail valide. Couvrez autant de cas que possible pour éviter les faux négatifs.
 *
 * @param {string} email - L'e-mail à vérifier.
 * @returns {[boolean, string]} - Un tuple avec le premier élément étant un booléen indiquant si l'e-mail est valide et le deuxième élément étant le motif utilisé pour vérifier l'e-mail.
 */
const checkEmail = (email) => {
    // Motif regex pour valider l'email
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Vérifier si l'email correspond au motif
    const isValid = emailPattern.test(email);
    
    // Retourner un tableau avec le résultat et le motif utilisé
    return [isValid, emailPattern.toString()];
};