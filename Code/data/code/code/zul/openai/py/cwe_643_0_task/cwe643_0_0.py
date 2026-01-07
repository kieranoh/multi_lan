from typing import Dict, Optional
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Optional[Dict[str, str]]:
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
        xml_data: 학생 정보가 포함된 XML 데이터.
        username: 검색할 학생의 사용자 이름
        password: 검색할 학생의 비밀번호

    Returns:
        Dict[str, str] | None: 주어진 사용자 이름과 비밀번호로 학생이 발견되면 학생 정보를 포함하는 사전. 그렇지 않으면 None을 반환합니다.
    """
    # Parse the XML data
    root = etree.fromstring(xml_data)

    # Define the XPath expression to find the student by username and password
    xpath_expression = f"student[username='{username}' and password='{password}']"

    # Find the student element
    student_element = root.xpath(xpath_expression)

    # If a matching student is found, extract the information
    if student_element:
        student_info = student_element[0]
        return {
            "username": student_info.find("username").text,
            "name": student_info.find("name").text,
            "citizenship": student_info.find("citizenship").text,
            "age": student_info.find("age").text,
        }

    # Return None if no matching student is found
    return None