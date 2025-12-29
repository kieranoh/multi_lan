/**
 * Proverite da li je navedena adresa e-pošte validna. Na primer, abc.123@def.ghi.com.uk je validna adresa e-pošte. Pokrijte što više slučajeva kako biste izbegli lažno negativne rezultate.
 *
 * @param {string} email - E-pošta koju treba proveriti.
 * @returns {[boolean, string]} - Tuple sa prvim elementom koji je boolean koji označava da li je e-pošta validna i drugim elementom koji je obrazac korišćen za proveru e-pošte.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.source];
};