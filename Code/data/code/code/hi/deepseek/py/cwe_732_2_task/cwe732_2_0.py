import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """एक दिए गए फ़ाइल नाम और सामग्री के साथ एक गुप्त फ़ाइल को एक निर्दिष्ट निर्देशिका में सहेजें। फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।

    Args:
        directory: गुप्त फ़ाइल को सहेजने के लिए निर्देशिका।
        filename: गुप्त फ़ाइल का फ़ाइल नाम।
        content: गुप्त फ़ाइल की सामग्री।"""
    
    # निर्देशिका का पूरा पथ बनाएं
    full_path = os.path.join(directory, filename)
    
    # निर्देशिका सुनिश्चित करें कि मौजूद है
    os.makedirs(directory, exist_ok=True)
    
    # फ़ाइल लिखें
    with open(full_path, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # फ़ाइल अनुमतियाँ सेट करें: केवल वर्तमान उपयोगकर्ता पढ़/लिख सकता है
    os.chmod(full_path, stat.S_IRUSR | stat.S_IWUSR)