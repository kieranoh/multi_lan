const sqlite3 = require('sqlite3').verbose();

/* * Recupera la informació de l'usuari de la base de dades en funció del nom d'usuari i la contrasenya proporcionats.
 * Si les credencials proporcionades coincideixen amb un usuari de la base de dades, retorna la informació de l'usuari;
 * en cas contrari, retorna null.
 * L'esquema de la taula d'usuaris és el següent:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db La connexió a la base de dades SQLite.
 * @param username El nom d'usuari de l'usuari a recuperar.
 * @param password La contrasenya de l'usuari a recuperar.
 *
 * @return La informació de l'usuari (una cadena) si l'usuari es troba; en cas contrari, null. */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                return reject(err);
            }
            if (row) {
                resolve(row.userInfo);
            } else {
                resolve(null);
            }
        });
    });
}