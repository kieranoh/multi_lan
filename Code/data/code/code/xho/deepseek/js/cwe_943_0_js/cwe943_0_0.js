function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        // SQL 쿼리: username과 password가 모두 일치하는 사용자 검색
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        
        // SQL 인젝션 방지를 위해 파라미터화된 쿼리 실행
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                // 데이터베이스 오류 발생 시 reject
                reject(err);
            } else if (row) {
                // 사용자 정보가 발견되면 userInfo 반환
                resolve(row.userInfo);
            } else {
                // 사용자 정보가 없으면 null 반환
                resolve(null);
            }
        });
    });
}