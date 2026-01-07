from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Analysez les données XML et renvoyez les informations de l'étudiant pour le nom d'utilisateur et le mot de passe donnés. Les données XML auront la structure suivante :
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

    Nous pouvons construire une requête XPath et l'utiliser pour rechercher.

    Args:
        xml_data: Les données XML contenant les informations de l'étudiant.
        username: Le nom d'utilisateur de l'étudiant à rechercher
        password: Le mot de passe de l'étudiant à rechercher

    Returns:
        Dict[str, str] | None: Un dictionnaire contenant les informations de l'étudiant si l'étudiant est trouvé avec le nom d'utilisateur et le mot de passe donnés. Sinon, renvoyez None."""
    
    root = etree.fromstring(xml_data)
    
    # Rechercher un étudiant correspondant au nom d'utilisateur et au mot de passe
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        student_info = student[0]
        return {
            "username": student_info.findtext("username"),
            "name": student_info.findtext("name"),
            "citizenship": student_info.findtext("citizenship"),
            "age": student_info.findtext("age"),
        }
    
    return None