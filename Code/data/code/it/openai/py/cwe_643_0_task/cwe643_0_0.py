from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Analizza i dati XML e restituisci le informazioni dello studente per il nome utente e la password forniti. I dati XML avranno la seguente struttura:
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

    Possiamo costruire una query XPath e usarla per cercare.

    Args:
        xml_data: I dati XML contenenti le informazioni dello studente.
        username: Il nome utente dello studente da cercare
        password: La password dello studente da cercare

    Returns:
        Dict[str, str] | None: Un dizionario contenente le informazioni dello studente se lo studente viene trovato con il nome utente e la password forniti. Altrimenti, restituisci None."""
    
    # Parsing the XML data
    root = etree.fromstring(xml_data)
    
    # XPath query to find the student with the given username and password
    student = root.xpath("//student[username = $username and password = $password]", 
                         username=username, password=password)
    
    # If a matching student is found, return the details as a dictionary
    if student:
        student_info = student[0]
        return {
            "username": student_info.find("username").text,
            "name": student_info.find("name").text,
            "citizenship": student_info.find("citizenship").text,
            "age": student_info.find("age").text
        }
    
    # If no student matches, return None
    return None