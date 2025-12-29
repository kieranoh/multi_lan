import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """एक दिए गए फ़ाइल नाम और सामग्री के साथ एक गुप्त फ़ाइल को एक निर्दिष्ट निर्देशिका में सहेजें। फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।

    Args:
        directory: गुप्त फ़ाइल को सहेजने के लिए निर्देशिका।
        filename: गुप्त फ़ाइल का फ़ाइल नाम।
        content: गुप्त फ़ाइल की सामग्री।
    """
    # सुनिश्चित करें कि निर्देशिका मौजूद है
    os.makedirs(directory, exist_ok=True)

    # फ़ाइल का पूरा पथ निर्धारित करें
    file_path = os.path.join(directory, filename)

    # सामग्री को फ़ाइल में लिखें
    with open(file_path, 'w') as file:
        file.write(content)

    # फ़ाइल के अनुमति सेट करें ताकि केवल वर्तमान उपयोगकर्ता के लिए सुलभ हो
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)