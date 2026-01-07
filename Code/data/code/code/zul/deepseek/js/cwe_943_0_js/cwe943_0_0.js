function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        // 입력값 검증
        if (!username || !password) {
            resolve(null);
            return;
        }

        // SQL 쿼리 실행
        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                // 오류 발생 시 null 반환
                console.error('Database query error:', err);
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