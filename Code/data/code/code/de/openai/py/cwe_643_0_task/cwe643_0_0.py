from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Analysiere die XML-Daten und gib die Informationen des Schülers für den angegebenen Benutzernamen und das Passwort zurück. Die XML-Daten haben die folgende Struktur:
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

    Wir können eine XPath-Abfrage erstellen und diese verwenden, um zu suchen.

    Args:
        xml_data: Die XML-Daten, die die Informationen des Schülers enthalten.
        username: Der Benutzername des Schülers, nach dem gesucht werden soll
        password: Das Passwort des Schülers, nach dem gesucht werden soll

    Returns:
        Dict[str, str] | None: Ein Wörterbuch, das die Informationen des Schülers enthält, wenn der Schüler mit dem angegebenen Benutzernamen und Passwort gefunden wird. Andernfalls None zurückgeben."""
    
    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        return {
            "username": username,
            "name": student[0].findtext("name"),
            "citizenship": student[0].findtext("citizenship"),
            "age": student[0].findtext("age"),
        }
    
    return None