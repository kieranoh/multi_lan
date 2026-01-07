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

我们可以构建一个 XPath 查询并用它来搜索。

    Args:
        xml_data: 包含学生信息的 XML 数据。
        username: 要搜索的学生的用户名
        password: 要搜索的学生的密码

    Returns:
        Dict[str, str] | None: 如果找到具有给定用户名和密码的学生，则返回包含学生信息的字典。否则，返回 None。"""
    try:
        # 解析 XML 数据
        root = etree.fromstring(xml_data.encode('utf-8') if isinstance(xml_data, str) else xml_data)
        
        # 构建 XPath 查询来查找匹配用户名和密码的学生
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # 如果没有找到匹配的学生，返回 None
        if not student_element:
            return None
        
        # 获取第一个匹配的学生元素
        student = student_element[0]
        
        # 提取学生信息到字典中
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        return student_info
        
    except etree.XMLSyntaxError:
        # 如果 XML 数据格式无效，返回 None
        return None
    except Exception:
        # 处理其他可能的异常
        return None