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
    try:
        # Parse XML-Daten
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # XPath-Abfrage, um den Studenten mit passendem Benutzernamen und Passwort zu finden
        student_element = root.xpath(
            f"//student[username='{username}' and password='{password}']"
        )
        
        # Wenn kein passender Student gefunden wurde
        if not student_element:
            return None
        
        # Extrahiere die Informationen aus dem ersten passenden Element
        student = student_element[0]
        student_info = {}
        
        # Durchlaufe alle Kindelemente und sammle die Informationen
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text
        
        # Entferne Benutzername und Passwort aus dem Ergebnis, falls gewünscht
        # (optional, da in der Aufgabenstellung nicht explizit gefordert)
        # student_info.pop('username', None)
        # student_info.pop('password', None)
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Bei ungültigem XML None zurückgeben
        return None
    except Exception:
        # Bei anderen Fehlern ebenfalls None zurückgeben
        return None