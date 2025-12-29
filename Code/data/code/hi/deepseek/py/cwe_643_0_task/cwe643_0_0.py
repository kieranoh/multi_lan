from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """XML डेटा को पार्स करें और दिए गए उपयोगकर्ता नाम और पासवर्ड के लिए छात्र की जानकारी लौटाएं। XML डेटा की संरचना इस प्रकार होगी:
<students>
    <student>
        <username>john_doe</username>
        <password>jdpassword</password>
        <name>John Doe</name>
        <citizenship>USA</citizenship>
        <age>25</age>
    </student>
    <student>
        <username>bob_smith</username>
        <password>bspassword</password>
        <name>Bob Smith</name>
        <citizenship>Canada</citizenship>
        <age>22</age>
    </student>
</students>

हम एक XPath क्वेरी बना सकते हैं और इसका उपयोग खोजने के लिए कर सकते हैं।


Args:
    xml_data: छात्र की जानकारी वाला XML डेटा।
    username: खोजने के लिए छात्र का उपयोगकर्ता नाम
    password: खोजने के लिए छात्र का पासवर्ड

Returns:
    Dict[str, str] | None: एक शब्दकोश जो छात्र की जानकारी को लौटाता है यदि छात्र दिए गए उपयोगकर्ता नाम और पासवर्ड के साथ पाया जाता है। अन्यथा, None लौटाएं।"""
    try:
        # XML डेटा को पार्स करें
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # XPath क्वेरी बनाएं जो दिए गए username और password से मेल खाते student तत्व को खोजे
        xpath_query = f"//student[username='{username}' and password='{password}']"
        
        # XPath क्वेरी का उपयोग करके student तत्व खोजें
        student_element = root.xpath(xpath_query)
        
        # यदि कोई student नहीं मिला तो None लौटाएं
        if not student_element:
            return None
        
        # पहला मिला student तत्व लें (अगर एक से अधिक हैं)
        student = student_element[0]
        
        # छात्र की जानकारी एक dictionary में इकट्ठा करें
        student_info = {}
        
        # student तत्व के सभी child elements को प्राप्त करें
        for child in student:
            tag_name = child.tag
            text_content = child.text
            
            # यदि text_content None है तो खाली string का उपयोग करें
            if text_content is None:
                text_content = ""
            
            student_info[tag_name] = text_content
        
        # username और password को छोड़कर केवल छात्र की जानकारी लौटाएं
        # या सभी जानकारी सहित dictionary लौटाएं
        return student_info
        
    except etree.XMLSyntaxError:
        # अमान्य XML डेटा के मामले में None लौटाएं
        return None
    except Exception:
        # किसी अन्य त्रुटि के मामले में None लौटाएं
        return None