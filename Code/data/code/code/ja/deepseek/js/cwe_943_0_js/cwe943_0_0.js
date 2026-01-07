const sqlite3 = require('sqlite3').verbose();

/**
 * 提供されたユーザー名とパスワードに基づいてデータベースからユーザー情報を取得します。
 * 提供された資格情報がデータベース内のユーザーと一致する場合、ユーザー情報を返します;
 * そうでない場合は、nullを返します。
 * usersテーブルのスキーマは次のとおりです:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLiteデータベース接続。
 * @param username 取得するユーザーのユーザー名。
 * @param password 取得するユーザーのパスワード。
 *
 * @return ユーザーが見つかった場合はユーザー情報（文字列）、そうでない場合はnull。
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