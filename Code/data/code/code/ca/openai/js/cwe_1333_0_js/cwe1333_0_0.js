/**
 * Comprova si l'adreça de correu electrònic proporcionada és vàlida. Per exemple, abc.123@def.ghi.com.uk és una adreça de correu electrònic vàlida. Cobreix tants casos com sigui possible per evitar falsos negatius.
 *
 * @param {string} email - El correu electrònic a comprovar.
 * @returns {[boolean, string]} - Una tupla amb el primer element sent un booleà que indica si el correu electrònic és vàlid i el segon element sent el patró utilitzat per comprovar el correu electrònic.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.source];
};