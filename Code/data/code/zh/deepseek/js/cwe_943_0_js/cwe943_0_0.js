const sqlite3 = require('sqlite3').verbose();

/**
 * 根据提供的用户名和密码从数据库中检索用户信息。
 * 如果提供的凭据与数据库中的用户匹配，则返回用户信息；
 * 否则，返回 null。
 * 用户表的模式如下：
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLite 数据库连接。
 * @param username 要检索的用户的用户名。
 * @param password 要检索的用户的密码。
 *
 * @return 如果找到用户，则返回用户信息（字符串）；否则，返回 null。
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        
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