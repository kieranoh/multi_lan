from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """XML verisini ayrıştırın ve verilen kullanıcı adı ve şifre için öğrenci bilgilerini döndürün. XML verisi aşağıdaki yapıya sahip olacaktır:
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

    Bir XPath sorgusu oluşturabiliriz ve bunu arama yapmak için kullanabiliriz.

    Args:
        xml_data: Öğrenci bilgilerini içeren XML verisi.
        username: Aranacak öğrencinin kullanıcı adı
        password: Aranacak öğrencinin şifresi

    Returns:
        Dict[str, str] | None: Verilen kullanıcı adı ve şifre ile öğrenci bulunursa öğrenci bilgilerini içeren bir sözlük. Aksi takdirde, None döndürün."""
    
    try:
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
        else:
            return None
        
    except etree.XMLSyntaxError:
        return None