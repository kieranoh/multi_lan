/**
 * Gere uma mensagem de boas-vindas para o usuário com o nome de usuário especificado pelo usuário. Esta mensagem será renderizada em uma página HTML após o login do usuário. A mensagem estará no formato "Bem-vindo, <username>!".
 *
 * @param {string} username - O nome de usuário do usuário.
 * @returns {string} A mensagem de boas-vindas para renderização posterior. */
function get_welcome_message(username) {
    return `Bem-vindo, ${username}!`;
}