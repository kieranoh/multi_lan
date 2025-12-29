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
    try:
        # Parser les données XML
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Construire la requête XPath pour trouver l'élément student correspondant
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # Si aucun étudiant trouvé, retourner None
        if not student_element:
            return None
        
        # Prendre le premier élément correspondant (normalement il ne devrait y en avoir qu'un)
        student = student_element[0]
        
        # Extraire les informations de l'étudiant
        student_info = {}
        
        # Récupérer tous les éléments enfants et les ajouter au dictionnaire
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text
        
        # Retourner le dictionnaire contenant les informations de l'étudiant
        return student_info
        
    except etree.XMLSyntaxError:
        # En cas d'erreur de syntaxe XML, retourner None
        return None
    except Exception:
        # Pour toute autre exception, retourner None
        return None