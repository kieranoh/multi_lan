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
    
    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        return {
            "username": student[0].find("username").text,
            "name": student[0].find("name").text,
            "citizenship": student[0].find("citizenship").text,
            "age": student[0].find("age").text
        }
    
    return None