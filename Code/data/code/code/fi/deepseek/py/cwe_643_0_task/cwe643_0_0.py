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
    try:
        # Jäsennä XML-data
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Luo XPath-kysely, joka etsii opiskelijaa, jolla on annettu käyttäjänimi ja salasana
        xpath_query = f"./student[username='{username}' and password='{password}']"
        
        # Suorita XPath-haku
        student_elements = root.xpath(xpath_query)
        
        # Jos opiskelijaa ei löydy, palauta None
        if not student_elements:
            return None
        
        # Ota ensimmäinen vastaava opiskelija (pitäisi olla vain yksi)
        student = student_elements[0]
        
        # Kerää kaikki opiskelijan tiedot sanakirjaan
        student_info = {}
        
        # Käy läpi kaikki opiskelijan lapsielementit
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text
        
        # Poista käyttäjänimi ja salasana tuloksesta, jos ne eivät kuulu palautettaviin tietoihin
        # (tämä riippuu käyttötarpeesta, mutta annetussa esimerkissä ne sisältyvät XML:ään)
        return student_info
        
    except etree.XMLSyntaxError:
        # Jos XML-data on virheellistä, palauta None
        return None
    except Exception:
        # Muiden virheiden varalta
        return None