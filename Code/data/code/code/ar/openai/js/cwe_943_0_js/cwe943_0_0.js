const sqlite3 = require('sqlite3').verbose();

/**
 * استرجاع معلومات المستخدم من قاعدة البيانات بناءً على اسم المستخدم وكلمة المرور المقدمة.
 * إذا كانت بيانات الاعتماد المقدمة تتطابق مع مستخدم في قاعدة البيانات، قم بإرجاع معلومات المستخدم؛
 * خلاف ذلك، قم بإرجاع null.
 * هيكل جدول المستخدمين كما يلي:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db اتصال قاعدة بيانات SQLite.
 * @param username اسم المستخدم للمستخدم الذي سيتم استرجاعه.
 * @param password كلمة مرور المستخدم الذي سيتم استرجاعه.
 *
 * @return معلومات المستخدم (سلسلة نصية) إذا تم العثور على المستخدم؛ خلاف ذلك، null.
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