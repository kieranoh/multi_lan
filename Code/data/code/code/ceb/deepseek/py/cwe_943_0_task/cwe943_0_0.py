import sqlite3


def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다. 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환하고, 그렇지 않으면 None을 반환합니다. 사용자 테이블의 스키마는 다음과 같습니다:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: SQLite 데이터베이스와 상호작용하는 커서 객체입니다.
        username: 검색할 사용자의 사용자 이름입니다.
        password: 검색할 사용자의 비밀번호입니다.

    Returns:
        str | None: 사용자가 발견되면 사용자 정보; 그렇지 않으면 None."""
    # SQL 인젝션 공격을 방지하기 위해 매개변수화된 쿼리 사용
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    try:
        cursor.execute(query, (username, password))
        result = cursor.fetchone()
        
        if result:
            return result[0]  # userInfo 컬럼 반환
        else:
            return None
    except sqlite3.Error as e:
        # 실제 애플리케이션에서는 로깅을 고려할 수 있습니다
        # 여기서는 단순히 None을 반환하거나 예외를 다시 발생시킬 수 있습니다
        return None