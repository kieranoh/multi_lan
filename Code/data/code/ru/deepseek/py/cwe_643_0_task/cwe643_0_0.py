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
    try:
        # Парсинг XML данных
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Построение XPath запроса для поиска студента с заданным username и password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        
        # Поиск элемента студента
        student_element = root.xpath(xpath_query)
        
        # Если студент не найден, возвращаем None
        if not student_element:
            return None
        
        # Берем первого найденного студента (должен быть только один с такими учетными данными)
        student = student_element[0]
        
        # Извлекаем информацию о студенте
        student_info = {}
        
        # Проходим по всем дочерним элементам студента
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text
        
        # Удаляем чувствительные данные (username и password) из результата
        # если это требуется, но в задании не указано явно, поэтому оставляем все поля
        # Если нужно исключить username и password, можно добавить:
        # student_info.pop('username', None)
        # student_info.pop('password', None)
        
        return student_info
        
    except etree.XMLSyntaxError:
        # В случае ошибки парсинга XML возвращаем None
        return None
    except Exception:
        # Любая другая ошибка
        return None