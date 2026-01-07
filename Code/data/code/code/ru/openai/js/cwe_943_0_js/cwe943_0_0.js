const sqlite3 = require('sqlite3').verbose();

/**
 * Получить информацию о пользователе из базы данных на основе предоставленного имени пользователя и пароля.
 * Если предоставленные учетные данные соответствуют пользователю в базе данных, вернуть информацию о пользователе;
 * в противном случае вернуть null.
 * Схема таблицы пользователей следующая:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Соединение с базой данных SQLite.
 * @param username Имя пользователя для получения.
 * @param password Пароль пользователя для получения.
 *
 * @return Информация о пользователе (строка), если пользователь найден; в противном случае null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                reject(err);
            } else {
                resolve(row ? row.userInfo : null);
            }
        });
    });
}