const sqlite3 = require('sqlite3').verbose();

/**
 * Preuzmite informacije o korisniku iz baze podataka na osnovu datog korisničkog imena i lozinke.
 * Ako se dati podaci poklapaju sa korisnikom u bazi podataka, vratite informacije o korisniku;
 * u suprotnom, vratite null.
 * Šema tabele korisnika je sledeća:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Veza sa SQLite bazom podataka.
 * @param username Korisničko ime korisnika koji se preuzima.
 * @param password Lozinka korisnika koji se preuzima.
 *
 * @return Informacije o korisniku (string) ako je korisnik pronađen; u suprotnom, null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        
        db.get(sql, [username, password], (err, row) => {
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