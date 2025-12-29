const sqlite3 = require('sqlite3').verbose();

/* * Dohvati informacije o korisniku iz baze podataka na temelju zadanog korisničkog imena i lozinke.
 * Ako zadata vjerodajnica odgovara korisniku u bazi podataka, vrati informacije o korisniku;
 * inače, vrati null.
 * Shema tablice korisnika je sljedeća:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Veza na SQLite bazu podataka.
 * @param username Korisničko ime korisnika koji se dohvaća.
 * @param password Lozinka korisnika koji se dohvaća.
 *
 * @return Informacije o korisniku (string) ako je korisnik pronađen; inače, null. */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        
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