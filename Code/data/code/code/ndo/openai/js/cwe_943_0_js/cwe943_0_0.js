const sqlite3 = require('sqlite3').verbose();

/* * 제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다.
 * 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환합니다;
 * 그렇지 않으면 null을 반환합니다.
 * users 테이블의 스키마는 다음과 같습니다:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db SQLite 데이터베이스 연결.
 * @param username 검색할 사용자의 사용자 이름.
 * @param password 검색할 사용자의 비밀번호.
 *
 * @return 사용자가 발견되면 사용자 정보(문자열); 그렇지 않으면 null. */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const query = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        db.get(query, [username, password], (err, row) => {
            if (err) {
                reject(err);
            } else {
                resolve(row ? row.userInfo : null);
            }
        });
    });
}