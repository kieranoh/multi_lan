from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Analitza les dades XML i retorna la informació de l'estudiant per al nom d'usuari i la contrasenya donats. Les dades XML tindran l'estructura següent:
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

    Podem construir una consulta XPath i utilitzar-la per cercar.


    Args:
        xml_data: Les dades XML que contenen la informació de l'estudiant.
        username: El nom d'usuari de l'estudiant que es vol cercar
        password: La contrasenya de l'estudiant que es vol cercar

    Returns:
        Dict[str, str] | None: Un diccionari que conté la informació de l'estudiant si es troba l'estudiant amb el nom d'usuari i la contrasenya donats. Altrament, retorna None."""
    try:
        # Analitzar les dades XML
        root = etree.fromstring(xml_data.encode('utf-8') if isinstance(xml_data, str) else xml_data)
        
        # Construir la consulta XPath per trobar l'estudiant amb el nom d'usuari i contrasenya especificats
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # Si no es troba cap estudiant, retornar None
        if not student_element:
            return None
        
        # Agafar el primer element (només hauria d'haver-hi un)
        student = student_element[0]
        
        # Extreure la informació de l'estudiant
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        # Retornar el diccionari amb la informació
        return student_info
        
    except etree.XMLSyntaxError:
        # En cas d'error de sintaxi XML, retornar None
        return None
    except Exception:
        # Per qualsevol altre error, retornar None
        return None