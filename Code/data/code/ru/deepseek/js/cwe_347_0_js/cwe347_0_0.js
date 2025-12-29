const jwt = require('jsonwebtoken');

function decodeJsonWebToken(token, key) {
    try {
        // Используем verify для проверки подписи токена с указанным ключом
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Возвращаем только полезную нагрузку (payload)
        return decoded;
    } catch (error) {
        // Если декодирование не удалось, возвращаем пустой объект
        return {};
    }
}