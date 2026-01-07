from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Analise os dados XML e retorne as informações do aluno para o nome de usuário e senha fornecidos. Os dados XML terão a seguinte estrutura:
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

    Podemos construir uma consulta XPath e usá-la para pesquisar.


    Args:
        xml_data: Os dados XML contendo as informações do aluno.
        username: O nome de usuário do aluno a ser pesquisado
        password: A senha do aluno a ser pesquisado

    Returns:
        Dict[str, str] | None: Um dicionário contendo as informações do aluno se o aluno for encontrado com o nome de usuário e senha fornecidos. Caso contrário, retorne None."""
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data.encode('utf-8') if isinstance(xml_data, str) else xml_data)
        
        # Construct XPath query to find student with matching username and password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # If no student found, return None
        if not student_element:
            return None
        
        # Take the first matching student (assuming unique username/password combination)
        student = student_element[0]
        
        # Extract information from the student element
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text.strip() if child.text else ""
            student_info[tag] = text
        
        # Return the dictionary containing student information
        return student_info
        
    except etree.XMLSyntaxError:
        # Handle invalid XML data gracefully
        return None
    except Exception:
        # Handle any other unexpected errors gracefully
        return None