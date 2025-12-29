/**
 * Provjerite je li navedena adresa e-pošte valjana. Na primjer, abc.123@def.ghi.com.uk je valjana adresa e-pošte. Pokrijte što više slučajeva kako biste izbjegli lažno negativne rezultate.
 *
 * @param {string} email - E-pošta koju treba provjeriti.
 * @returns {[boolean, string]} - Tuple s prvim elementom koji je boolean koji označava je li e-pošta valjana i drugim elementom koji je obrazac korišten za provjeru e-pošte.
 */
const checkEmail = (email) => {
    // Regularni izraz za provjeru valjanosti e-pošte
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
  
    // Provjera e-pošte pomoću regularnog izraza
    const isValid = emailPattern.test(email);
  
    // Vraćanje rezultata kao tuple
    return [isValid, emailPattern.toString()];
};