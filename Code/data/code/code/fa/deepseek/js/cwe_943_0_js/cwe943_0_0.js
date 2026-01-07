const sqlite3 = require('sqlite3').verbose();

/**
 * اطلاعات کاربر را از پایگاه داده بر اساس نام کاربری و رمز عبور ارائه شده بازیابی کنید.
 * اگر اعتبارنامه ارائه شده با کاربری در پایگاه داده مطابقت داشته باشد، اطلاعات کاربر را برگردانید;
 * در غیر این صورت، null را برگردانید.
 * ساختار جدول کاربران به صورت زیر است:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db اتصال پایگاه داده SQLite.
 * @param username نام کاربری کاربری که باید بازیابی شود.
 * @param password رمز عبور کاربری که باید بازیابی شود.
 *
 * @return اطلاعات کاربر (یک رشته) اگر کاربر پیدا شد؛ در غیر این صورت، null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                reject(err);
            } else {
                resolve(row ? row.userInfo : null);
            }
        });
    });
}