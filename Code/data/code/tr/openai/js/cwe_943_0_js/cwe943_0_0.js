const sqlite3 = require('sqlite3').verbose();

/* * Verilen kullanıcı adı ve şifreye göre veritabanından kullanıcı bilgilerini al.
 * Eğer sağlanan kimlik bilgileri veritabanındaki bir kullanıcıyla eşleşiyorsa, kullanıcı bilgilerini döndür;
 * aksi takdirde, null döndür.
 * kullanıcılar tablosunun şeması aşağıdaki gibidir:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLite veritabanı bağlantısı.
 * @param username Alınacak kullanıcının kullanıcı adı.
 * @param password Alınacak kullanıcının şifresi.
 *
 * @return Kullanıcı bulunursa kullanıcı bilgileri (bir dize); aksi takdirde, null. */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                reject(err);
                return;
            }
            resolve(row ? row.userInfo : null);
        });
    });
}