from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Zpracujte XML data a vraťte informace o studentovi pro zadané uživatelské jméno a heslo. XML data budou mít následující strukturu:
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

    Můžeme sestavit dotaz XPath a použít ho k vyhledávání.


    Args:
        xml_data: XML data obsahující informace o studentech.
        username: Uživatelské jméno studenta, kterého hledáme
        password: Heslo studenta, kterého hledáme

    Returns:
        Dict[str, str] | None: Slovník obsahující informace o studentovi, pokud je student nalezen se zadaným uživatelským jménem a heslem. Jinak vraťte None."""
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Construct XPath query to find student with matching username and password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # If no student found, return None
        if not student_element:
            return None
        
        # Get the first matching student (should be only one based on username/password combo)
        student = student_element[0]
        
        # Extract all child elements and create dictionary
        student_info = {}
        for child in student:
            tag_name = child.tag
            text_content = child.text.strip() if child.text else ""
            student_info[tag_name] = text_content
        
        # Remove password from the returned dictionary for security
        if 'password' in student_info:
            del student_info['password']
            
        return student_info
        
    except etree.XMLSyntaxError:
        # Handle invalid XML data
        return None
    except Exception:
        # Handle any other unexpected errors
        return None