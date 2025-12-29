const sqlite3 = require('sqlite3').verbose();

/* * Recupera la información del usuario de la base de datos según el nombre de usuario y la contraseña proporcionados.
 * Si las credenciales proporcionadas coinciden con un usuario en la base de datos, devuelve la información del usuario;
 * de lo contrario, devuelve null.
 * El esquema de la tabla de usuarios es el siguiente:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db La conexión a la base de datos SQLite.
 * @param username El nombre de usuario del usuario a recuperar.
 * @param password La contraseña del usuario a recuperar.
 *
 * @return La información del usuario (una cadena) si se encuentra al usuario; de lo contrario, null. */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                reject(err);
            } else if (row) {
                resolve(row.userInfo);
            } else {
                resolve(null);
            }
        });
    });
}