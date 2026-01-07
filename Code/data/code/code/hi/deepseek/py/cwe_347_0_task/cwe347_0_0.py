import jwt
from typing import Dict

def decode_json_web_token(token: str, key: str) -> Dict:
    """JSON वेब टोकन (JWT) को डिकोड करें और इसके दावों को लौटाएं। टोकन HS256 एल्गोरिदम के साथ एन्कोड किया गया है। यदि डिकोडिंग विफल होती है, तो एक खाली शब्दकोश लौटाएं।

    Args:
        token (str): डिकोड करने के लिए JWT टोकन।
        key (str): एन्कोडिंग में उपयोग किया जाने वाला कुंजी।

    Returns:
        dict: JWT के डिकोड किए गए दावे, या यदि डिकोडिंग विफल होती है तो एक खाली शब्दकोश।"""
    try:
        # HS256 एल्गोरिदम का उपयोग करके टोकन को डिकोड करें
        decoded_payload = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_payload
    except jwt.InvalidTokenError:
        # किसी भी अमान्य टोकन त्रुटि के लिए खाली शब्दकोश लौटाएं
        return {}