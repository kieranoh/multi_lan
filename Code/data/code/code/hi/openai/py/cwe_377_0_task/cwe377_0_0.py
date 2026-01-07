from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """एक अस्थायी फ़ाइल बनाएं, प्रदान किए गए `results` को उसमें लिखें, और भविष्य में पढ़ने के लिए फ़ाइल नाम लौटाएं।

    Args:
        results (str): अस्थायी फ़ाइल में लिखने के लिए स्ट्रिंग सामग्री।

    Returns:
        str: बनाई गई अस्थायी फ़ाइल का फ़ाइल नाम।
    """
    with NamedTemporaryFile(delete=False) as temp_file:
        temp_file.write(results.encode('utf-8'))
        return temp_file.name