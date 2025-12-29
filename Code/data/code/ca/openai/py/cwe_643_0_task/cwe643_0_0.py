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
    
    root = etree.fromstring(xml_data)
    xpath_query = f"student[username='{username}' and password='{password}']"
    student_element = root.xpath(xpath_query)

    if student_element:
        student_info = student_element[0]
        return {
            "username": student_info.findtext("username"),
            "name": student_info.findtext("name"),
            "citizenship": student_info.findtext("citizenship"),
            "age": student_info.findtext("age"),
        }
    
    return None