from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Parsa XML-data och returnera studentinformationen för det angivna användarnamnet och lösenordet. XML-datan kommer att ha följande struktur:
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

    Vi kan konstruera en XPath-fråga och använda den för att söka.


    Args:
        xml_data: XML-datan som innehåller studentinformationen.
        username: Användarnamnet för studenten som ska sökas efter
        password: Lösenordet för studenten som ska sökas efter

    Returns:
        Dict[str, str] | None: En ordbok som innehåller studentinformationen om studenten hittas med det angivna användarnamnet och lösenordet. Annars, returnera None."""
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Construct XPath query to find student with matching username and password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        
        # Find the student element
        student_element = root.xpath(xpath_query)
        
        # If no student found, return None
        if not student_element:
            return None
        
        # Take the first matching student (should be only one)
        student = student_element[0]
        
        # Extract information from the student element
        student_info = {}
        
        # Get all child elements and their text content
        for child in student.getchildren():
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Handle invalid XML
        return None
    except Exception:
        # Handle any other exceptions
        return None