/**
 * Kontrollera om den angivna e-postadressen är giltig. Till exempel, abc.123@def.ghi.com.uk är en giltig e-postadress. Täck så många fall som möjligt för att undvika falska negativa.
 *
 * @param {string} email - E-posten som ska kontrolleras.
 * @returns {[boolean, string]} - En tuple där det första elementet är en boolean som indikerar om e-posten är giltig och det andra elementet är mönstret som används för att kontrollera e-posten.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.toString()];
};