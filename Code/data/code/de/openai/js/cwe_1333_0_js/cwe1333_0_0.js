/**
 * Überprüfen Sie, ob die angegebene E-Mail-Adresse gültig ist. Zum Beispiel ist abc.123@def.ghi.com.uk eine gültige E-Mail-Adresse. Decken Sie so viele Fälle wie möglich ab, um falsche Negative zu vermeiden.
 *
 * @param {string} email - Die zu überprüfende E-Mail.
 * @returns {[boolean, string]} - Ein Tupel, bei dem das erste Element ein Boolean ist, das angibt, ob die E-Mail gültig ist, und das zweite Element das Muster ist, das zur Überprüfung der E-Mail verwendet wurde.
 */
const checkEmail = (email) => {
    // Regulärer Ausdruck zur Überprüfung des E-Mail-Formats
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;

    // Überprüfen, ob die E-Mail dem Muster entspricht
    const isValid = emailPattern.test(email);

    // Rückgabe des Ergebnisses und des verwendeten Musters
    return [isValid, emailPattern.toString()];
};