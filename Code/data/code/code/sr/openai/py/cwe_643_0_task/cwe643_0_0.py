from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Parsirati XML podatke i vratiti informacije o studentu za dati korisničko ime i lozinku. XML podaci će imati sledeću strukturu:
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

    Možemo konstruisati XPath upit i koristiti ga za pretragu.

    Args:
        xml_data: XML podaci koji sadrže informacije o studentu.
        username: Korisničko ime studenta koji se traži
        password: Lozinka studenta koji se traži

    Returns:
        Dict[str, str] | None: Rečnik koji sadrži informacije o studentu ako je student pronađen sa datim korisničkim imenom i lozinkom. U suprotnom, vrati None."""
    
    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )

    if student:
        return {
            "username": student[0].findtext("username"),
            "name": student[0].findtext("name"),
            "citizenship": student[0].findtext("citizenship"),
            "age": student[0].findtext("age"),
        }
    return None