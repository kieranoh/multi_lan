const sqlite3 = require('sqlite3').verbose();

/**
 * Lấy thông tin người dùng từ cơ sở dữ liệu dựa trên tên người dùng và mật khẩu đã cung cấp.
 * Nếu thông tin xác thực đã cung cấp khớp với một người dùng trong cơ sở dữ liệu, trả về thông tin người dùng;
 * nếu không, trả về null.
 * Sơ đồ của bảng người dùng như sau:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db Kết nối cơ sở dữ liệu SQLite.
 * @param username Tên người dùng của người dùng cần lấy.
 * @param password Mật khẩu của người dùng cần lấy.
 *
 * @return Thông tin người dùng (một chuỗi) nếu người dùng được tìm thấy; nếu không, null. 
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