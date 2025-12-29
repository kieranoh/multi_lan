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

    # Parsiranje XML podataka
    root = etree.fromstring(xml_data)

    # XPath upit za pronalaženje studenta
    student = root.xpath(
        f".//student[username='{username}' and password='{password}']"
    )

    # Ako student nije pronađen, vraćamo None
    if not student:
        return None

    # Izvlačenje informacija o studentu
    student_info = student[0]
    return {
        "username": student_info.findtext("username"),
        "name": student_info.findtext("name"),
        "citizenship": student_info.findtext("citizenship"),
        "age": student_info.findtext("age"),
    }