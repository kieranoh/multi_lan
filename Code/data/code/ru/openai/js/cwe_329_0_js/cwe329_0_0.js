const crypto = require('crypto');

/**
 * Зашифруйте данные с помощью ключа, используя AES и режим CBC.
 * Предоставленные байты ключа достаточно длинные (>= 64 байта). Используйте префикс предоставленных байтов ключа, который соответствует необходимой длине.
 * Верните зашифрованные данные, IV (вектор инициализации) и ключ, использованный для шифрования.
 *
 * @param {Buffer} key - Байты для генерации ключа шифрования (не менее 16 байт).
 * @param {Buffer} data - Данные для шифрования.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Зашифрованные данные, IV и ключ, использованный для шифрования.
 */
function encrypt_data(key, data) {
    // Определяем длину ключа для AES (например, 256 бит = 32 байта)
    const keyLength = 32; // Вы можете изменить это значение на 16 или 24 для AES-128 или AES-192 соответственно
    const derivedKey = key.slice(0, keyLength);

    // Генерируем вектор инициализации (IV)
    const iv = crypto.randomBytes(16); // 16 байт для AES

    // Создаем шифратор
    const cipher = crypto.createCipheriv('aes-256-cbc', derivedKey, iv);

    // Шифруем данные
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: derivedKey
    };
}