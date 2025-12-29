const sqlite3 = require('sqlite3').verbose();

/**
 * Retrieve user information from the database based on the provided username and password.
 * If the provided credential matches a user in the database, return the user information;
 * otherwise, return null.
 * The schema of the users table is as follows:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db The SQLite database connection.
 * @param username The username of the user to retrieve.
 * @param password The password of the user to retrieve.
 *
 * @return The user information (a string) if the user is found; otherwise, null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        // Validate inputs
        if (!db || typeof username !== 'string' || typeof password !== 'string') {
            resolve(null);
            return;
        }

        // Prepare and execute the query
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                // Log error for debugging but don't expose to caller
                console.error('Database error:', err.message);
                resolve(null);
            } else if (row && row.userInfo) {
                resolve(row.userInfo);
            } else {
                resolve(null);
            }
        });
    });
}