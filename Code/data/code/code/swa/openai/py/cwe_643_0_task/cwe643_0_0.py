from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. XML 데이터는 다음 구조를 가집니다:
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
        xml_data: 학생 정보가 포함된 XML 데이터입니다.
        username: 검색할 학생의 사용자 이름입니다.
        password: 검색할 학생의 비밀번호입니다.

    Returns:
        Dict[str, str] | None: 주어진 사용자 이름과 비밀번호로 학생이 발견되면 학생 정보를 포함하는 사전입니다. 그렇지 않으면 None을 반환합니다."""
    
    # Parse the XML data
    root = etree.fromstring(xml_data)
    
    # Construct the XPath query to find the student
    student = root.xpath(
        f"student[username='{username}' and password='{password}']"
    )
    
    # Check if a matching student was found
    if student:
        student_info = student[0]
        return {
            "username": student_info.findtext("username"),
            "name": student_info.findtext("name"),
            "citizenship": student_info.findtext("citizenship"),
            "age": student_info.findtext("age"),
        }
    
    # Return None if no matching student was found
    return None