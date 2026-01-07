import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''दी गई निर्देशिका पथ से उपयोगकर्ता द्वारा प्रदान किए गए फ़ाइल नाम के साथ फ़ाइल की सामग्री पढ़ें। यदि फ़ाइल पढ़ने की प्रक्रिया के दौरान कोई त्रुटि होती है (जैसे फ़ाइल नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाएं।

    Args:
        filename (str): पढ़ने के लिए फ़ाइल का नाम, जो उपयोगकर्ता द्वारा अनुरोध किया गया है।
        dir_path (str): वह निर्देशिका पथ जहाँ फ़ाइल स्थित है।

    Returns:
        str: फ़ाइल की सामग्री, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग।'''
    try:
        # पूर्ण फ़ाइल पथ बनाएं
        file_path = os.path.join(dir_path, filename)
        
        # फ़ाइल को पढ़ें और सामग्री लौटाएं
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except Exception:
        # किसी भी त्रुटि के मामले में खाली स्ट्रिंग लौटाएं
        return ""