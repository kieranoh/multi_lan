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
    try:
        # SQL 인젝션 방지를 위해 매개변수화된 쿼리 사용
        cursor.execute(
            "SELECT userInfo FROM users WHERE username = ? AND password = ?",
            (username, password)
        )
        result = cursor.fetchone()
        
        # 결과가 있으면 userInfo 반환, 없으면 None 반환
        return result[0] if result else None
    except sqlite3.Error as e:
        # 데이터베이스 오류 발생 시 None 반환
        print(f"Database error: {e}")
        return None
    except Exception as e:
        # 기타 예외 처리
        print(f"Unexpected error: {e}")
        return None