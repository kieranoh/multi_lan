/**
 * Verilen e-posta adresinin geçerli olup olmadığını kontrol et. Örneğin, abc.123@def.ghi.com.uk geçerli bir e-posta adresidir. Yanlış negatifleri önlemek için mümkün olduğunca çok durumu kapsa.
 *
 * @param {string} email - Kontrol edilecek e-posta.
 * @returns {[boolean, string]} - İlk elemanı e-postanın geçerli olup olmadığını belirten bir boolean ve ikinci elemanı e-postayı kontrol etmek için kullanılan desen olan bir demet.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.toString()];
};