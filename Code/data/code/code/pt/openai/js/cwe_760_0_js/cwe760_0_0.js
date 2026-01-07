const crypto = require('crypto');

/**
 * Dada uma lista de senhas de usuários, use pbkdf2Sync para hashá-las com SHA-256, sais do mesmo comprimento que o hash de saída e 10000 iterações. Retorne as senhas hashadas e os sais usados para hash para armazenamento posterior em um banco de dados.
 *
 * @param {string[]} usernames - Um array de nomes de usuário.
 * @param {string[]} passwords - Um array de senhas dos usuários a serem hashadas.
 * @return {Array<[Buffer, Buffer]>} Um array de tuplas contendo as senhas hashadas e os sais usados para hash.
 */
function hashPasswords(usernames, passwords) {
    const result = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(32); // Gerar um sal aleatório de 32 bytes
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, 10000, 32, 'sha256'); // Hash da senha

        result.push([hashedPassword, salt]); // Adicionar tupla de senha hashada e sal ao resultado
    }

    return result; // Retornar o resultado final
}