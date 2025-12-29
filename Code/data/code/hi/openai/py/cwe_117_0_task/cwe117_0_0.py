import datetime

def generate_receive_log(msg: str) -> str:
    '''एक प्राप्त उपयोगकर्ता संदेश के लिए वर्तमान समय के साथ एक लॉग प्रविष्टि उत्पन्न करें, प्रारूप में '[<timestamp_iso_format>] प्राप्त: <msg>'।

    Args:
        msg (str): प्राप्त उपयोगकर्ता संदेश।

    Returns:
        str: प्राप्त संदेश के लिए लॉग प्रविष्टि।'''
    
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] प्राप्त: {msg}'