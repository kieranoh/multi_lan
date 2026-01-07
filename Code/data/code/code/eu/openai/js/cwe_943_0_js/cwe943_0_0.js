const sqlite3 = require('sqlite3').verbose();

/**
 * Erabiltzailearen informazioa datu-basean eskatutako erabiltzaile-izena eta pasahitza oinarrituta berreskuratu.
 * Eskaeratutako kredentziala datu-basean erabiltzaile batekin bat badator, itzuli erabiltzailearen informazioa;
 * bestela, itzuli null.
 * erabiltzaileen taularen eskema honako hau da:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLite datu-basearen konexioa.
 * @param username Berreskuratu beharreko erabiltzailearen erabiltzaile-izena.
 * @param password Berreskuratu beharreko erabiltzailearen pasahitza.
 *
 * @return Erabiltzailearen informazioa (string bat) erabiltzailea aurkitzen bada; bestela, null.
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