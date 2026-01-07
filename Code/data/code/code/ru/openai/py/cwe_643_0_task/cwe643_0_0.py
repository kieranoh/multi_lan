from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Парсите XML-данные и возвращайте информацию о студенте для данного имени пользователя и пароля. XML-данные будут иметь следующую структуру:
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

    Мы можем построить запрос XPath и использовать его для поиска.

    Args:
        xml_data: XML-данные, содержащие информацию о студенте.
        username: Имя пользователя студента, которого нужно найти
        password: Пароль студента, которого нужно найти

    Returns:
        Dict[str, str] | None: Словарь, содержащий информацию о студенте, если студент найден с данным именем пользователя и паролем. В противном случае верните None."""
    
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