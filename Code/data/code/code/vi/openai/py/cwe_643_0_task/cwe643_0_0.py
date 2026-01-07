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
    
    root = etree.fromstring(xml_data)
    student = root.xpath(f"//student[username='{username}' and password='{password}']")
    
    if student:
        student_info = student[0]
        return {
            "username": student_info.findtext('username'),
            "name": student_info.findtext('name'),
            "citizenship": student_info.findtext('citizenship'),
            "age": student_info.findtext('age'),
        }
    
    return None