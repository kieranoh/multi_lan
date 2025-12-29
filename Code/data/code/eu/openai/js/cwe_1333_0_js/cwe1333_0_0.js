/**
 * Egin egiaztatu emandako posta elektronikoa baliozkoa den. Adibidez, abc.123@def.ghi.com.uk posta elektroniko baliozkoa da. 
 * Faltsuak saihesteko kasu gehienak estali.
 *
 * @param {string} email - Egiaztatu beharreko posta elektronikoa.
 * @returns {boolean} - Emaitzak egiaztatutako posta elektronikoa baliozkoa den edo ez.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    return emailPattern.test(email);
};