from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Parse de XML-gegevens en retourneer de studenteninformatie voor de gegeven gebruikersnaam en wachtwoord. De XML-gegevens hebben de volgende structuur:
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

    We kunnen een XPath-query opstellen en deze gebruiken om te zoeken.


    Args:
        xml_data: De XML-gegevens die de studenteninformatie bevatten.
        username: De gebruikersnaam van de student om naar te zoeken
        password: Het wachtwoord van de student om naar te zoeken

    Returns:
        Dict[str, str] | None: Een woordenboek met de studenteninformatie als de student is gevonden met de gegeven gebruikersnaam en wachtwoord. Anders, retourneer None."""
    
    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        student_info = student[0]
        return {
            'username': student_info.find('username').text,
            'name': student_info.find('name').text,
            'citizenship': student_info.find('citizenship').text,
            'age': student_info.find('age').text,
        }
    
    return None