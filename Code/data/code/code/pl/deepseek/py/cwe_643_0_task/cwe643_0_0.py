from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Przeanalizuj dane XML i zwróć informacje o studencie dla podanej nazwy użytkownika i hasła. Dane XML będą miały następującą strukturę:
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

    Możemy skonstruować zapytanie XPath i użyć go do wyszukiwania.


    Args:
        xml_data: Dane XML zawierające informacje o studentach.
        username: Nazwa użytkownika studenta, którego szukasz
        password: Hasło studenta, którego szukasz

    Returns:
        Dict[str, str] | None: Słownik zawierający informacje o studencie, jeśli student zostanie znaleziony z podaną nazwą użytkownika i hasłem. W przeciwnym razie zwróć None."""
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Construct XPath query to find student with matching username and password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # If no student found, return None
        if not student_element:
            return None
        
        # Take the first matching student (should be only one)
        student = student_element[0]
        
        # Extract all child elements and build dictionary
        student_info = {}
        for child in student:
            tag_name = child.tag
            text_content = child.text.strip() if child.text else ""
            student_info[tag_name] = text_content
        
        # Remove username and password from the dictionary as they're credentials
        student_info.pop('username', None)
        student_info.pop('password', None)
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Handle invalid XML
        return None
    except Exception:
        # Handle any other unexpected errors
        return None