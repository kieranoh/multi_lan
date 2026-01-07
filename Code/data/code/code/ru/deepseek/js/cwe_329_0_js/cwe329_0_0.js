const crypto = require('crypto');

function encrypt_data(key, data) {
    // Проверка входных параметров
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('key и data должны быть Buffer');
    }
    
    if (key.length < 16) {
        throw new Error('key должен содержать не менее 16 байт');
    }
    
    // AES-256-CBC требует ключ длиной 32 байта (256 бит)
    const keyLength = 32;
    
    // Используем префикс ключа необходимой длины
    const keyUsed = key.slice(0, keyLength);
    
    // Генерируем случайный IV длиной 16 байт (стандартный для AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Создаем шифр с использованием AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Шифруем данные
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // Объединяем зашифрованные данные
    const encryptedData = Buffer.concat(encryptedChunks);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}