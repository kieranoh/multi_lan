const sqlite3 = require('sqlite3').verbose();

/**
 * प्रदान किए गए उपयोगकर्ता नाम और पासवर्ड के आधार पर डेटाबेस से उपयोगकर्ता जानकारी प्राप्त करें।
 * यदि प्रदान की गई क्रेडेंशियल डेटाबेस में किसी उपयोगकर्ता से मेल खाती है, तो उपयोगकर्ता जानकारी लौटाएं;
 * अन्यथा, null लौटाएं।
 * उपयोगकर्ताओं की तालिका का स्कीमा इस प्रकार है:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLite डेटाबेस कनेक्शन।
 * @param username उस उपयोगकर्ता का उपयोगकर्ता नाम जिसे प्राप्त करना है।
 * @param password उस उपयोगकर्ता का पासवर्ड जिसे प्राप्त करना है।
 *
 * @return यदि उपयोगकर्ता पाया जाता है तो उपयोगकर्ता जानकारी (एक स्ट्रिंग); अन्यथा, null।
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