import sqlite3

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> str | None:
    """उपयोगकर्ता नाम और पासवर्ड के आधार पर डेटाबेस से उपयोगकर्ता जानकारी प्राप्त करें। यदि प्रदान किया गया प्रमाण पत्र डेटाबेस में किसी उपयोगकर्ता से मेल खाता है, तो उपयोगकर्ता जानकारी लौटाएं; अन्यथा, None लौटाएं। उपयोगकर्ताओं की तालिका का स्कीमा इस प्रकार है:

    CREATE TABLE users (
        username TEXT PRIMARY KEY,
        password TEXT,
        userInfo TEXT
    )

    Args:
        cursor: SQLite डेटाबेस के साथ इंटरैक्ट करने के लिए एक कर्सर ऑब्जेक्ट।
        username: उस उपयोगकर्ता का उपयोगकर्ता नाम जिसे प्राप्त करना है।
        password: उस उपयोगकर्ता का पासवर्ड जिसे प्राप्त करना है।

    Returns:
        str | None: यदि उपयोगकर्ता पाया जाता है तो उपयोगकर्ता जानकारी; अन्यथा, None।"""
    
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None