from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """解析 XML 数据并返回给定用户名和密码的学生信息。XML 数据将具有以下结构：
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

    Args:
        xml_data: 包含学生信息的 XML 数据。
        username: 要搜索的学生的用户名
        password: 要搜索的学生的密码

    Returns:
        Dict[str, str] | None: 如果找到具有给定用户名和密码的学生，则返回包含学生信息的字典。否则，返回 None。
    """
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
    
    return None