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
    
    try:
        # Parsear el XML
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Construir la consulta XPath para encontrar el estudiante con username y password específicos
        xpath_query = f"//student[username='{username}' and password='{password}']"
        
        # Buscar el nodo del estudiante
        student_node = root.xpath(xpath_query)
        
        # Si no se encuentra ningún estudiante, retornar None
        if not student_node:
            return None
        
        # Tomar el primer estudiante que coincida (debería ser único)
        student = student_node[0]
        
        # Extraer la información del estudiante
        student_info = {}
        
        # Obtener todos los elementos hijos del nodo estudiante
        for child in student.getchildren():
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        # Retornar el diccionario con la información del estudiante
        return student_info
        
    except etree.XMLSyntaxError:
        # En caso de error en el parsing del XML, retornar None
        return None
    except Exception:
        # Para cualquier otro error, retornar None
        return None