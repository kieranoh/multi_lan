from typing import Dict

from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """XML datua parseatu eta emandako erabiltzaile izena eta pasahitzarentzako ikaslearen informazioa itzuli. XML datuak honako egitura izango du:
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

XPath galdera bat eraiki dezakegu eta bilatzeko erabili.

    Args:
        xml_data: Ikaslearen informazioa duen XML datua.
        username: Bilatu beharreko ikaslearen erabiltzaile izena
        password: Bilatu beharreko ikaslearen pasahitza

    Returns:
        Dict[str, str] | None: Ikaslearen informazioa duen hitzordua, ikaslea emandako erabiltzaile izena eta pasahitzarekin aurkitzen bada. Bestela, itzuli None."""
    try:
        # Parseatu XML datua
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Eraiki XPath adierazpena erabiltzaile izena eta pasahitza parekatzen duen ikaslea bilatzeko
        xpath_query = f"//student[username='{username}' and password='{password}']"
        
        # Bilatu ikaslea XPath erabiliz
        student_element = root.xpath(xpath_query)
        
        # Konprobatu ikaslea aurkitu den
        if not student_element:
            return None
            
        # Hartu lehenengo ikasle elementua (bakar bat egon beharko luke)
        student = student_element[0]
        
        # Bilatu beharreko etiketak
        tags_to_extract = ['username', 'password', 'name', 'citizenship', 'age']
        student_info = {}
        
        for tag in tags_to_extract:
            element = student.find(tag)
            if element is not None and element.text is not None:
                student_info[tag] = element.text
            else:
                student_info[tag] = ""
        
        return student_info
        
    except etree.XMLSyntaxError:
        # XML datua baliogabea bada
        return None
    except Exception:
        # Beste edozein errore
        return None