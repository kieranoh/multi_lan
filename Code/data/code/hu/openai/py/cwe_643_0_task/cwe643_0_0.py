from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Parsd a XML adatokat, és térj vissza a hallgatói információkkal a megadott felhasználónév és jelszó alapján. A XML adatok a következő struktúrával rendelkeznek:
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

    Létrehozhatunk egy XPath lekérdezést, és használhatjuk a kereséshez.

    Args:
        xml_data: A XML adat, amely a hallgatói információkat tartalmazza.
        username: A keresett hallgató felhasználóneve
        password: A keresett hallgató jelszava

    Returns:
        Dict[str, str] | None: Egy szótár, amely a hallgatói információkat tartalmazza, ha a hallgató megtalálható a megadott felhasználónévvel és jelszóval. Ellenkező esetben None-t ad vissza."""
    
    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"//student[username='{username}' and password='{password}']"
    )
    
    if student:
        return {
            "username": username,
            "name": student[0].findtext("name"),
            "citizenship": student[0].findtext("citizenship"),
            "age": student[0].findtext("age"),
        }
    
    return None