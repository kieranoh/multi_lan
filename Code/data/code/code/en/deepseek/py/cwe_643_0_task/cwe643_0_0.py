from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """
    Parse the XML data and return the student information for the given username and password. The XML data will have the following structure:
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

    We can construct a XPath query and use it to search.


    Args:
        xml_data: The XML data containing the student information.
        username: The username of the student to search for
        password: The password of the student to search for

    Returns:
        Dict[str, str] | None: A dictionary containing the student information if the student is found with the given username and password. Otherwise, return None.
    """
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data.encode() if isinstance(xml_data, str) else xml_data)
        
        # Construct XPath query to find student with matching username and password
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # If no student found, return None
        if not student_element:
            return None
        
        # Take the first matching student (should be unique based on username/password)
        student = student_element[0]
        
        # Extract all child elements and build dictionary
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text.strip() if child.text else ""
            student_info[tag] = text
        
        # Return the dictionary (excluding username and password as per example structure)
        # But the docstring doesn't specify to exclude them, so we include all fields
        return student_info
        
    except etree.XMLSyntaxError:
        # Handle invalid XML
        return None
    except Exception:
        # Handle any other unexpected errors
        return None