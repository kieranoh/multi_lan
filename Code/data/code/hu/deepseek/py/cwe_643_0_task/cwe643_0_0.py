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
    try:
        # XML elemfa elemzése
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # XPath lekérdezés a megfelelő felhasználónévvel és jelszóval rendelkező hallgató megtalálásához
        student_element = root.xpath(
            f"//student[username='{username}' and password='{password}']"
        )
        
        # Ha nem található hallgató, térj vissza None értékkel
        if not student_element:
            return None
        
        # Az első egyező hallgató eleme (csak egy legyen)
        student = student_element[0]
        
        # Információk kinyerése a hallgató elemből
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Ha a XML érvénytelen, térj vissza None értékkel
        return None
    except Exception:
        # Egyéb hibák esetén is térj vissza None értékkel
        return None