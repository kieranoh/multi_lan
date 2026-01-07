const sqlite3 = require('sqlite3').verbose();

/**
 * Recupera le informazioni dell'utente dal database in base al nome utente e alla password forniti.
 * Se le credenziali fornite corrispondono a un utente nel database, restituisci le informazioni dell'utente;
 * altrimenti, restituisci null.
 * Lo schema della tabella utenti è il seguente:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db La connessione al database SQLite.
 * @param username Il nome utente dell'utente da recuperare.
 * @param password La password dell'utente da recuperare.
 *
 * @return Le informazioni dell'utente (una stringa) se l'utente è trovato; altrimenti, null.
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