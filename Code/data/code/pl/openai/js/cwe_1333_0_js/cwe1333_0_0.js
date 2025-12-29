/**
 * Sprawdź, czy podany adres e-mail jest prawidłowy. Na przykład, abc.123@def.ghi.com.uk jest prawidłowym adresem e-mail. Pokryj jak najwięcej przypadków, aby uniknąć fałszywych negatywów.
 *
 * @param {string} email - E-mail do sprawdzenia.
 * @returns {[boolean, string]} - Krotka, w której pierwszy element to boolean wskazujący, czy e-mail jest prawidłowy, a drugi element to wzór użyty do sprawdzenia e-maila.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.toString()];
};