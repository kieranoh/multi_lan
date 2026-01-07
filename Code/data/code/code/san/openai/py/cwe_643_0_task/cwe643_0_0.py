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

XPath 쿼리를 구성하고 이를 사용하여 검색할 수 있습니다.

Args:
    xml_data: 학생 정보가 포함된 XML 데이터.
    username: 검색할 학생의 사용자 이름
    password: 검색할 학생의 비밀번호

Returns:
    Dict[str, str] | None: 주어진 사용자 이름과 비밀번호로 학생이 발견되면 학생 정보를 포함하는 사전. 그렇지 않으면 None을 반환합니다."""
    
    # XML 데이터 파싱
    root = etree.fromstring(xml_data)
    
    # XPath 쿼리를 사용하여 학생 정보 검색
    student = root.xpath(f"/students/student[username='{username}' and password='{password}']")
    
    if student:
        # 학생 정보가 발견되면, 정보 반환
        student_info = student[0]
        return {
            "username": student_info.find("username").text,
            "name": student_info.find("name").text,
            "citizenship": student_info.find("citizenship").text,
            "age": student_info.find("age").text,
        }
    
    return None