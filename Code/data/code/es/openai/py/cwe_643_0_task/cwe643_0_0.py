from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Analiza los datos XML y devuelve la información del estudiante para el nombre de usuario y la contraseña dados. Los datos XML tendrán la siguiente estructura:
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

    Podemos construir una consulta XPath y usarla para buscar.


    Args:
        xml_data: Los datos XML que contienen la información del estudiante.
        username: El nombre de usuario del estudiante a buscar
        password: La contraseña del estudiante a buscar

    Returns:
        Dict[str, str] | None: Un diccionario que contiene la información del estudiante si se encuentra al estudiante con el nombre de usuario y la contraseña dados. De lo contrario, devuelve None."""
    
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
            "age": student_info.find("age").text,
        }
    
    return None