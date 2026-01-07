import tarfile
import os

def extract_tar_to_path(tar_path: str, dest_path: str) -> bool:
    '''दी गई गंतव्य पथ पर tar फ़ाइल की सामग्री निकालें। यदि निकासी सफल होती है, तो True लौटाएं; अन्यथा, यदि निकासी प्रक्रिया के दौरान कोई त्रुटि होती है (जैसे फ़ाइल नहीं मिली, अनुमति त्रुटि, सभी सामग्री निकालने में असमर्थ), तो बस False लौटाएं।

    Args:
        tar_path: tar फ़ाइल का पथ
        dest_path: गंतव्य फ़ोल्डर का पथ

    Returns:
        यदि निकासी सफल होती है तो True; अन्यथा, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False