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
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data.encode('utf-8') if isinstance(xml_data, str) else xml_data)
        
        # Construct XPath query to find student with matching username and password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        if not student_element:
            return None
        
        # Take the first matching student (should be only one if usernames are unique)
        student = student_element[0]
        
        # Extract all child elements and create dictionary
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        # Remove username and password from the dictionary as they're credentials
        student_info.pop('username', None)
        student_info.pop('password', None)
        
        return student_info if student_info else None
        
    except etree.XMLSyntaxError:
        # Handle invalid XML
        return None
    except Exception:
        # Handle any other exceptions
        return None