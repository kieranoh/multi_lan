const crypto = require('crypto');

function hashPasswords(usernames, passwords) {
    // Проверка входных данных
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('usernames и passwords должны быть массивами');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('Массивы usernames и passwords должны иметь одинаковую длину');
    }
    
    const results = [];
    const keyLength = 32; // Длина хеша SHA-256 в байтах
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        
        // Проверка, что пароль является строкой
        if (typeof password !== 'string') {
            throw new TypeError(`Пароль с индексом ${i} должен быть строкой`);
        }
        
        // Генерация случайной соли той же длины, что и выходной хеш
        const salt = crypto.randomBytes(keyLength);
        
        // Хеширование пароля с использованием pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(
            password,          // пароль для хеширования
            salt,              // соль
            10000,             // количество итераций
            keyLength,         // длина ключа в байтах
            'sha256'           // алгоритм хеширования
        );
        
        // Добавление результата в массив
        results.push([hashedPassword, salt]);
    }
    
    return results;
}