const sqlite3 = require('sqlite3').verbose();

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