import sqlite3
from typing import Optional

def get_user(cursor: sqlite3.Cursor, username: str, password: str) -> Optional[str]:
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
    
    # SQL क्वेरी जो username और password दोनों से मेल खाती है
    query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    try:
        # पैरामीटराइज्ड क्वेरी निष्पादित करें (SQL इंजेक्शन से बचाव के लिए)
        cursor.execute(query, (username, password))
        
        # परिणाम प्राप्त करें
        result = cursor.fetchone()
        
        # यदि कोई परिणाम मिलता है, तो userInfo लौटाएं
        if result:
            return result[0]  # userInfo कॉलम
        else:
            return None
    
    except sqlite3.Error as e:
        # डेटाबेस त्रुटि के मामले में, None लौटाएं या त्रुटि लॉग करें
        # वास्तविक अनुप्रयोग में, आप त्रुटि को उचित तरीके से संभालना चाहेंगे
        print(f"Database error: {e}")
        return None