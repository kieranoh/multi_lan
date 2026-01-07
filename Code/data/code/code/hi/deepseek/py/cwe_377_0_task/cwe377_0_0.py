import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
from typing import Optional


def write_results(results: str) -> str:
    """एक अस्थायी फ़ाइल बनाएं, प्रदान किए गए `results` को उसमें लिखें, और भविष्य में पढ़ने के लिए फ़ाइल नाम लौटाएं।

    Args:
        results (str): अस्थायी फ़ाइल में लिखने के लिए स्ट्रिंग सामग्री।

    Returns:
        str: बनाई गई अस्थायी फ़ाइल का फ़ाइल नाम।
    """
    # NamedTemporaryFile का उपयोग करके एक अस्थायी फ़ाइल बनाएं
    # 'delete=False' सेट करें ताकि फ़ाइल स्वचालित रूप से नष्ट न हो
    # 'mode='w'' सेट करें क्योंकि हम स्ट्रिंग लिख रहे हैं
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # प्रदान की गई सामग्री को फ़ाइल में लिखें
        temp_file.write(results)
        # फ़ाइल का नाम लौटाएं
        return temp_file.name