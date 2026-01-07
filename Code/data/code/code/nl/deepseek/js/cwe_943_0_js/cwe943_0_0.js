const sqlite3 = require('sqlite3').verbose();

/**
 * Haal gebruikersinformatie op uit de database op basis van de opgegeven gebruikersnaam en wachtwoord.
 * Als de opgegeven inloggegevens overeenkomen met een gebruiker in de database, retourneer dan de gebruikersinformatie;
 * anders, retourneer null.
 * Het schema van de tabel gebruikers is als volgt:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db De SQLite-databaseverbinding.
 * @param username De gebruikersnaam van de gebruiker die moet worden opgehaald.
 * @param password Het wachtwoord van de gebruiker die moet worden opgehaald.
 *
 * @return De gebruikersinformatie (een string) als de gebruiker is gevonden; anders, null.
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