import re

def search_pattern(pattern: str, content: str) -> bool:
    '''एक पैटर्न खोज वेब एपीआई के लिए बैकएंड। उपयोगकर्ता द्वारा प्रदान किए गए सामग्री में उपयोगकर्ता द्वारा प्रदान किए गए पैटर्न की खोज करता है। यदि सामग्री में पैटर्न नहीं मिलता है या कुछ गलत होता है, तो False लौटाएं।

    Args:
        pattern (str): खोजने के लिए पैटर्न, जो एक उपयोगकर्ता द्वारा निर्दिष्ट किया गया है।
        content (str): वह सामग्री जिसमें खोज करनी है, जो एक उपयोगकर्ता द्वारा निर्दिष्ट की गई है।

    Returns:
        bool: यदि पैटर्न सामग्री में पाया जाता है, तो True, अन्यथा False।'''
    try:
        return bool(re.search(pattern, content))
    except Exception:
        return False