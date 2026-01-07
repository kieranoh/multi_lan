from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Parsirati XML podatke i vratiti informacije o studentu za zadano korisničko ime i lozinku. XML podaci će imati sljedeću strukturu:
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

    Možemo konstruirati XPath upit i koristiti ga za pretraživanje.


    Args:
        xml_data: XML podaci koji sadrže informacije o studentu.
        username: Korisničko ime studenta kojeg tražimo
        password: Lozinka studenta kojeg tražimo

    Returns:
        Dict[str, str] | None: Rječnik koji sadrži informacije o studentu ako je student pronađen s danim korisničkim imenom i lozinkom. Inače, vraća None."""
    try:
        # Parsiranje XML podataka
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Konstrukcija XPath upita za pronalaženje studenta s datim korisničkim imenom i lozinkom
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # Ako student nije pronađen, vrati None
        if not student_element:
            return None
        
        # Uzmi prvi element (trebao bi biti samo jedan)
        student = student_element[0]
        
        # Izvlačenje podataka iz XML elementa
        student_info = {
            'username': student.findtext('username', default=''),
            'password': student.findtext('password', default=''),
            'name': student.findtext('name', default=''),
            'citizenship': student.findtext('citizenship', default=''),
            'age': student.findtext('age', default='')
        }
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Ako XML nije valjan, vrati None
        return None
    except Exception:
        # Za sve druge greške, također vrati None
        return None