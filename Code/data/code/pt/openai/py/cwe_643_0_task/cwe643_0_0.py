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
    
    root = etree.fromstring(xml_data)
    xpath_query = f"student[username='{username}' and password='{password}']"
    student_element = root.xpath(xpath_query)

    if student_element:
        student = student_element[0]
        return {
            "username": student.findtext("username"),
            "name": student.findtext("name"),
            "citizenship": student.findtext("citizenship"),
            "age": student.findtext("age"),
        }
    
    return None