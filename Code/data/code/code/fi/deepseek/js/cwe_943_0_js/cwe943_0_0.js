const sqlite3 = require('sqlite3').verbose();

/* * Hae käyttäjätiedot tietokannasta annetun käyttäjänimen ja salasanan perusteella.
 * Jos annettu tunnistetieto vastaa käyttäjää tietokannassa, palauta käyttäjätiedot;
 * muuten palauta null.
 * Käyttäjät-taulun skeema on seuraava:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLite-tietokantayhteys.
 * @param username Haettavan käyttäjän käyttäjänimi.
 * @param password Haettavan käyttäjän salasana.
 *
 * @return Käyttäjätiedot (merkkijono), jos käyttäjä löytyy; muuten null. */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                reject(err);
            } else {
                resolve(row ? row.userInfo : null);
            }
        });
    });
}