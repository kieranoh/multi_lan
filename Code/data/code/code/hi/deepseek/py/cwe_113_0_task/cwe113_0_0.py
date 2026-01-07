from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''दी गई जानकारी को निर्दिष्ट प्रकार के तहत मौजूदा HTTP प्रतिक्रिया हेडर डिक्शनरी में संग्रहीत करें।
यह फ़ंक्शन निम्नलिखित जानकारी प्रकारों पर विचार करता है: 'lang', 'encoding', 'cache'। इन्हें क्रमशः 'Accept-Language', 'Accept-Encoding', और 'Cache-Control' के रूप में कुंजी के रूप में संग्रहीत किया जाता है।
जानकारी की सामग्री उपयोगकर्ता अनुरोधों से पढ़ी जाती है।
यदि निर्दिष्ट जानकारी प्रकार मान्य है, तो अपडेट की गई प्रतिक्रिया हेडर में इसे होना चाहिए। यदि कुछ गलत होता है, तो फ़ंक्शन को मूल हेडर डिक्शनरी को बिना किसी परिवर्तन के लौटाना चाहिए।

    Args:
        info_type (str): हेडर में संग्रहीत करने के लिए जानकारी का प्रकार।
        info_content (str): हेडर में संग्रहीत करने के लिए जानकारी की सामग्री।
        header (Dict[str, str]): मौजूदा प्रतिक्रिया हेडर डिक्शनरी।

    Returns:
        Dict[str, str]: संग्रहीत जानकारी के साथ अपडेट की गई प्रतिक्रिया हेडर डिक्शनरी।'''
    try:
        # Create a copy of the original header to avoid modifying the input
        updated_header = header.copy()
        
        # Map info_type to corresponding header key
        header_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        }
        
        # Check if info_type is valid
        if info_type in header_mapping:
            # Get the corresponding header key
            header_key = header_mapping[info_type]
            
            # Store the info_content in the header
            updated_header[header_key] = info_content
            
            return updated_header
        else:
            # Invalid info_type, return original header unchanged
            return header
            
    except Exception:
        # If anything goes wrong, return the original header unchanged
        return header