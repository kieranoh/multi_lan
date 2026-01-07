const crypto = require('crypto');

/**
 * Надежно захешируйте данный пароль и верните хеш в виде строки.
 *
 * @param {string} password - Пароль, который нужно захешировать.
 * @returns {Promise<string>} Надежно захешированный пароль.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Генерируем случайную соль
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Создаем хеш с использованием алгоритма scrypt (рекомендуется для паролей)
            crypto.scrypt(password, salt, 64, (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Формируем финальный хеш в формате: алгоритм:соль:хеш
                const hash = `scrypt:${salt}:${derivedKey.toString('hex')}`;
                resolve(hash);
            });
        } catch (error) {
            reject(error);
        }
    });
}