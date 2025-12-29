from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Jäsennä XML-tiedot ja palauta opiskelijatiedot annetulle käyttäjänimelle ja salasanalle. XML-tiedoilla on seuraava rakenne:
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

    Voimme rakentaa XPath-kyselyn ja käyttää sitä hakemiseen.

    Args:
        xml_data: XML-tiedot, jotka sisältävät opiskelijatiedot.
        username: Opiskelijan käyttäjänimi, jota etsitään
        password: Opiskelijan salasana, jota etsitään

    Returns:
        Dict[str, str] | None: Sanakirja, joka sisältää opiskelijatiedot, jos opiskelija löytyy annetulla käyttäjänimellä ja salasanalla. Muuten, palauta None."""
    
    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        student_info = student[0]
        return {
            "username": student_info.findtext("username"),
            "name": student_info.findtext("name"),
            "citizenship": student_info.findtext("citizenship"),
            "age": student_info.findtext("age"),
        }
    
    return None