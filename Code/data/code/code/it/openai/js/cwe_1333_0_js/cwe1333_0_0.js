/**
 * Controlla se l'indirizzo email fornito è valido. Ad esempio, abc.123@def.ghi.com.uk è un indirizzo email valido. Copri quanti più casi possibile per evitare falsi negativi.
 *
 * @param {string} email - L'email da controllare.
 * @returns {[boolean, string]} - Una tupla con il primo elemento che è un booleano che indica se l'email è valida e il secondo elemento che è il modello utilizzato per controllare l'email.
 */
const checkEmail = (email) => {
    // Definisco il modello regex per un'email valida
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Controllo se l'email corrisponde al modello
    const isValid = emailPattern.test(email);
    
    // Restituisco la tupla con il risultato e il modello utilizzato
    return [isValid, emailPattern.toString()];
};