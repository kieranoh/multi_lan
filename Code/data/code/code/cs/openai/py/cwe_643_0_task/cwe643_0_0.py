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
    
    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        student_info = student[0]
        return {
            "username": student_info.find("username").text,
            "name": student_info.find("name").text,
            "citizenship": student_info.find("citizenship").text,
            "age": student_info.find("age").text
        }
    
    return None