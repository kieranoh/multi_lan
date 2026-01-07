/**
 * 제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다.
 * 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환합니다;
 * 그렇지 않으면 null을 반환합니다.
 * 
 * @param {sqlite3.Database} db - SQLite 데이터베이스 연결 객체
 * @param {string} username - 검색할 사용자의 사용자 이름
 * @param {string} password - 검색할 사용자의 비밀번호
 * @returns {Promise<string|null>} - 사용자 정보 문자열 또는 null
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        // 입력값 검증
        if (!username || !password) {
            resolve(null);
            return;
        }

        // SQL 쿼리 - 매개변수화된 쿼리를 사용하여 SQL 인젝션 방지
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        
        // 데이터베이스 쿼리 실행
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                // 오류 발생 시 null 반환
                console.error('데이터베이스 쿼리 오류:', err.message);
                resolve(null);
                return;
            }
            
            // 결과 처리
            if (row && row.userInfo) {
                resolve(row.userInfo);
            } else {
                resolve(null);
            }
        });
    });
}

// 함수 내보내기 (CommonJS 모듈 시스템용)
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { getUser };
}