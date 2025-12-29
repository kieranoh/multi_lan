const sqlite3 = require('sqlite3').verbose();

/**
 * Získejte informace o uživateli z databáze na základě zadaného uživatelského jména a hesla.
 * Pokud zadané údaje odpovídají uživateli v databázi, vraťte informace o uživateli;
 * jinak vraťte null.
 * Schéma tabulky uživatelů je následující:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Připojení k databázi SQLite.
 * @param username Uživatelské jméno uživatele, jehož informace se mají získat.
 * @param password Heslo uživatele, jehož informace se mají získat.
 *
 * @return Informace o uživateli (řetězec), pokud je uživatel nalezen; jinak null.
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