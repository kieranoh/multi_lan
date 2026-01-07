from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Phân tích dữ liệu XML và trả về thông tin sinh viên cho tên người dùng và mật khẩu đã cho. Dữ liệu XML sẽ có cấu trúc sau:
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

    Chúng ta có thể xây dựng một truy vấn XPath và sử dụng nó để tìm kiếm.


    Args:
        xml_data: Dữ liệu XML chứa thông tin sinh viên.
        username: Tên người dùng của sinh viên cần tìm
        password: Mật khẩu của sinh viên cần tìm

    Returns:
        Dict[str, str] | None: Một từ điển chứa thông tin sinh viên nếu sinh viên được tìm thấy với tên người dùng và mật khẩu đã cho. Nếu không, trả về None."""
    try:
        # Parse XML data
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Build XPath query to find student with matching username and password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        
        # Find the student element
        student_elements = root.xpath(xpath_query)
        
        # If no student found, return None
        if not student_elements:
            return None
        
        # Get the first matching student (assuming unique username/password combination)
        student_element = student_elements[0]
        
        # Extract information from the student element
        student_info = {}
        
        # Get all child elements of the student element
        for child in student_element:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Handle invalid XML data
        return None
    except Exception:
        # Handle any other unexpected errors
        return None