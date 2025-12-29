query = "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username, password))
    result = cursor.fetchone()
    
    if result:
        return result[0]
    return None