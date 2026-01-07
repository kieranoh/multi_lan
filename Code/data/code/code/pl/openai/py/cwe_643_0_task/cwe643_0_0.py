from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Przeanalizuj dane XML i zwróć informacje o studencie dla podanej nazwy użytkownika i hasła. Dane XML będą miały następującą strukturę:
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

    Możemy skonstruować zapytanie XPath i użyć go do wyszukiwania.

    Args:
        xml_data: Dane XML zawierające informacje o studentach.
        username: Nazwa użytkownika studenta, którego szukasz
        password: Hasło studenta, którego szukasz

    Returns:
        Dict[str, str] | None: Słownik zawierający informacje o studencie, jeśli student zostanie znaleziony z podaną nazwą użytkownika i hasłem. W przeciwnym razie zwróć None."""
    
    # Parse the XML data
    root = etree.fromstring(xml_data)

    # Use XPath to find the student with the given username and password
    student = root.xpath(
        f".//student[username='{username}' and password='{password}']"
    )

    # If a matching student is found, retrieve their information
    if student:
        info = student[0]  # Get the first matching student
        return {
            'username': info.find('username').text,
            'name': info.find('name').text,
            'citizenship': info.find('citizenship').text,
            'age': info.find('age').text,
        }

    # Return None if no matching student is found
    return None