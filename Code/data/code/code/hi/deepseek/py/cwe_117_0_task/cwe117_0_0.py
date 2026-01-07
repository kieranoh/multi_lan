import datetime


def generate_receive_log(msg: str) -> str:
    '''एक प्राप्त उपयोगकर्ता संदेश के लिए वर्तमान समय के साथ एक लॉग प्रविष्टि उत्पन्न करें, प्रारूप में '[<timestamp_iso_format>] प्राप्त: <msg>'।

    Args:
        msg (str): प्राप्त उपयोगकर्ता संदेश।

    Returns:
        str: प्राप्त संदेश के लिए लॉग प्रविष्टि।'''
    # Get current UTC time in ISO 8601 format
    timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
    
    # Format the log entry as specified
    log_entry = f'[{timestamp}] प्राप्त: {msg}'
    
    return log_entry