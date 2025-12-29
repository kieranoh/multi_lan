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

    # XML datua parseatu
    root = etree.fromstring(xml_data)

    # XPath erabiliz ikaslearen informazioa bilatu
    student = root.xpath(
        f"/students/student[username='{username}' and password='{password}']"
    )

    # Ikaslea aurkitu bada, informazioa itzuli
    if student:
        return {
            "username": student[0].findtext("username"),
            "name": student[0].findtext("name"),
            "citizenship": student[0].findtext("citizenship"),
            "age": student[0].findtext("age"),
        }

    # Ikaslea aurkitu ez bada, None itzuli
    return None