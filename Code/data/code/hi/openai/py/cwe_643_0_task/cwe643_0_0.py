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
        Dict[str, str] | None: एक शब्दकोश जो छात्र की जानकारी को लौटाता है यदि छात्र दिए गए उपयोगकर्ता नाम और पासवर्ड के साथ पाया जाता है। अन्यथा, None लौटाएं।
    """
    root = etree.fromstring(xml_data)
    
    # XPath क्वेरी का उपयोग करके छात्र का पता लगाना
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        student_info = student[0]
        return {
            "name": student_info.find("name").text,
            "citizenship": student_info.find("citizenship").text,
            "age": student_info.find("age").text,
        }
    
    return None