from typing import Dict, Optional
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Optional[Dict[str, str]]:
    """Parses XML data and returns student information for the given username and password.
    
    The XML data has the following structure:
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
        xml_data: XML data containing student information.
        username: Username of the student to search for
        password: Password of the student to search for

    Returns:
        Dict[str, str] | None: A dictionary containing student information if found, otherwise None.
    """
    # Parse the XML data
    root = etree.fromstring(xml_data)
    
    # Define the XPath to find the student by username and password
    student_xpath = f"./student[username='{username}' and password='{password}']"
    student_element = root.xpath(student_xpath)

    # If a matching student is found, extract their information
    if student_element:
        student_info = student_element[0]
        return {
            'username': student_info.findtext('username'),
            'name': student_info.findtext('name'),
            'citizenship': student_info.findtext('citizenship'),
            'age': student_info.findtext('age')
        }
    
    # Return None if no matching student is found
    return None