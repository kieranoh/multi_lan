/**
 * Ellenőrizze, hogy a megadott e-mail cím érvényes-e. Például, abc.123@def.ghi.com.uk egy érvényes e-mail cím. Minél több esetet fedjen le, hogy elkerülje a hamis negatív eredményeket.
 *
 * @param {string} email - Az ellenőrizendő e-mail cím.
 * @returns {[boolean, string]} - Egy tuple, amelynek első eleme egy boolean, amely azt jelzi, hogy az e-mail érvényes-e, a második elem pedig a használt minta az e-mail ellenőrzésére.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.source];
};