import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """JSON वेब टोकन (JWT) को डिकोड करें और इसके दावों को लौटाएं। टोकन HS256 एल्गोरिदम के साथ एन्कोड किया गया है। यदि डिकोडिंग विफल होती है, तो एक खाली शब्दकोश लौटाएं।

    Args:
        token (str): डिकोड करने के लिए JWT टोकन।
        key (str): एन्कोडिंग में उपयोग किया जाने वाला कुंजी।

    Returns:
        dict: JWT के डिकोड किए गए दावे, या यदि डिकोडिंग विफल होती है तो एक खाली शब्दकोश।
    """
    try:
        # JWT को डिकोड करें
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        # सिग्नेचर समाप्त होने पर स्थिति
        return {}
    except jwt.InvalidTokenError:
        # यदि टोकन अमान्य है
        return {}