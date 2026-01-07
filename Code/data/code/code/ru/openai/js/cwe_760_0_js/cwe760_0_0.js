const crypto = require('crypto');

/**
 * Учитывая список паролей пользователей, используйте pbkdf2Sync для их хеширования с SHA-256, солью такой же длины, как и выходной хеш, и 10000 итерациями. Верните хешированные пароли и соли, использованные для хеширования, для дальнейшего хранения в базе данных.
 *
 * @param {string[]} usernames - Массив имен пользователей.
 * @param {string[]} passwords - Массив паролей пользователей для хеширования.
 * @return {Array<[Buffer, Buffer]>} Массив кортежей, содержащих хешированные пароли и соли, использованные для хеширования.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // Длина хеша SHA-256 в байтах
    const result = [];

    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(hashLength); // Генерация соли
        const hash = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256');
        result.push([hash, salt]);
    }

    return result;
}