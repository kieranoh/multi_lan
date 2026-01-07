/**
 * Verifique se o endereço de e-mail fornecido é válido. Por exemplo, abc.123@def.ghi.com.uk é um endereço de e-mail válido. Cubra o maior número possível de casos para evitar falsos negativos.
 *
 * @param {string} email - O e-mail a ser verificado.
 * @returns {[boolean, string]} - Uma tupla com o primeiro elemento sendo um booleano indicando se o e-mail é válido e o segundo elemento sendo o padrão usado para verificar o e-mail.
 */
const checkEmail = (email) => {
    // Expressão regular para validar um endereço de e-mail
    const regex = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = regex.test(email);
    return [isValid, regex.toString()];
};