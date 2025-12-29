const sqlite3 = require('sqlite3').verbose();

/**
 * Felhasználói információk lekérése az adatbázisból a megadott felhasználónév és jelszó alapján.
 * Ha a megadott hitelesítő adatok egyeznek egy felhasználóval az adatbázisban, térj vissza a felhasználói információkkal;
 * különben térj vissza null értékkel.
 * A felhasználók táblájának sémája a következő:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Az SQLite adatbázis kapcsolat.
 * @param username A lekérdezni kívánt felhasználó felhasználóneve.
 * @param password A lekérdezni kívánt felhasználó jelszava.
 *
 * @return A felhasználói információ (string), ha a felhasználó megtalálható; különben null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const query = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        
        db.get(query, [username, password], (err, row) => {
            if (err) {
                reject(err);
                return;
            }
            
            if (row) {
                resolve(row.userInfo);
            } else {
                resolve(null);
            }
        });
    });
}