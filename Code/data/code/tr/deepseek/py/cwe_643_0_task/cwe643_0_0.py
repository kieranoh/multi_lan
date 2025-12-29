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
        # XML verisini ayrıştır
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # XPath sorgusu ile kullanıcı adı ve şifre eşleşen öğrenciyi bul
        student_element = root.xpath(
            f"//student[username='{username}' and password='{password}']"
        )
        
        # Eğer öğrenci bulunamazsa None döndür
        if not student_element:
            return None
        
        # İlk eşleşen öğrenciyi al
        student = student_element[0]
        
        # Öğrenci bilgilerini sözlük olarak topla
        student_info = {}
        
        # Tüm alt elemanları dolaş
        for child in student:
            tag = child.tag
            text = child.text
            
            # Eğer metin None değilse sözlüğe ekle
            if text is not None:
                student_info[tag] = text
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Geçersiz XML formatı durumunda None döndür
        return None
    except Exception:
        # Diğer tüm hatalar için None döndür
        return None