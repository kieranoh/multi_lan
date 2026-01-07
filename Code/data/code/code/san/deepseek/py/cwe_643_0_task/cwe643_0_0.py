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
    try:
        # XML 파싱
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 찾기
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # 학생이 발견되지 않은 경우
        if not student_element:
            return None
        
        # 첫 번째 일치하는 학생 요소 가져오기
        student = student_element[0]
        
        # 학생 정보를 사전으로 추출
        student_info = {
            'username': student.find('username').text,
            'password': student.find('password').text,
            'name': student.find('name').text,
            'citizenship': student.find('citizenship').text,
            'age': student.find('age').text
        }
        
        return student_info
        
    except etree.XMLSyntaxError:
        # XML 파싱 오류 처리
        return None
    except Exception:
        # 기타 예외 처리
        return None