const sqlite3 = require('sqlite3').verbose();

/**
 * Hämta användarinformation från databasen baserat på det angivna användarnamnet och lösenordet.
 * Om de angivna uppgifterna matchar en användare i databasen, returnera användarinformationen;
 * annars, returnera null.
 * Schemat för användartabellen är som följer:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLite-databasanslutningen.
 * @param username Användarnamnet för den användare som ska hämtas.
 * @param password Lösenordet för den användare som ska hämtas.
 *
 * @return Användarinformationen (en sträng) om användaren hittas; annars, null.
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