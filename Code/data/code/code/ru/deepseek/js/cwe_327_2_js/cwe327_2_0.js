const crypto = require('crypto');

function encryptData(key, data) {
    // Выбираем AES-256-CBC (требует 32-байтовый ключ)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 256 бит
    
    // Берем первые keyLength байт из предоставленного ключа
    const aesKey = key.slice(0, keyLength);
    
    // Генерируем случайный IV (16 байт для AES)
    const iv = crypto.randomBytes(16);
    
    // Создаем шифратор
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Шифруем данные
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}