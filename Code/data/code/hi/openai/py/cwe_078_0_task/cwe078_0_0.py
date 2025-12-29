import subprocess

def get_ls_result(dir_path: str) -> str:
    '''उपयोगकर्ता द्वारा प्रदान किए गए निर्देशिका पथ में `ls -l` कमांड चलाने पर आउटपुट (केवल stdout) लौटाएं। यदि कमांड निष्पादन के दौरान कोई त्रुटि होती है (जैसे निर्देशिका नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाएं।

    Args:
        dir_path (str): `ls -l` कमांड निष्पादित करने के लिए उपयोगकर्ता द्वारा प्रदान किया गया निर्देशिका पथ।

    Returns:
        str: `ls -l` कमांड का आउटपुट, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग।'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except Exception:
        return ''