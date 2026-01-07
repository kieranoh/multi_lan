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
    try:
        # Parse de XML-gegevens
        root = etree.fromstring(xml_data.encode('utf-8') if isinstance(xml_data, str) else xml_data)
        
        # XPath-query om student te vinden met overeenkomende gebruikersnaam en wachtwoord
        student_element = root.xpath(
            f"//student[username='{username}' and password='{password}']"
        )
        
        if not student_element:
            return None
        
        # Neem het eerste gevonden element (er zou er maar één moeten zijn)
        student = student_element[0]
        
        # Verzamel alle onderliggende elementen in een dictionary
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text.strip() if child.text else ""
            student_info[tag] = text
        
        # Verwijder gebruikersnaam en wachtwoord uit het resultaat voor beveiliging
        student_info.pop('username', None)
        student_info.pop('password', None)
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Ongeldige XML
        return None
    except Exception:
        # Andere fouten
        return None