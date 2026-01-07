from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """داده‌های XML را تجزیه کرده و اطلاعات دانش‌آموز را برای نام کاربری و رمز عبور داده شده برگردانید. داده‌های XML دارای ساختار زیر خواهد بود:
    <students>
        <student>
            <username>john_doe</username>
            <password>jdpassword</password>
            <name>جان دو</name>
            <citizenship>آمریکا</citizenship>
            <age>۲۵</age>
        </student>
        <student>
            <username>bob_smith</username>
            <password>bspassword</password>
            <name>باب اسمیت</name>
            <citizenship>کانادا</citizenship>
            <age>۲۲</age>
        </student>
    </students>

    می‌توانیم یک پرس‌وجوی XPath بسازیم و از آن برای جستجو استفاده کنیم.


    Args:
        xml_data: داده‌های XML حاوی اطلاعات دانش‌آموز.
        username: نام کاربری دانش‌آموزی که باید جستجو شود
        password: رمز عبور دانش‌آموزی که باید جستجو شود

    Returns:
        Dict[str, str] | None: دیکشنری حاوی اطلاعات دانش‌آموز در صورت یافتن دانش‌آموز با نام کاربری و رمز عبور داده شده. در غیر این صورت، None را برگردانید."""
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # Build XPath query to find student with matching username and password
        # Using text() to get the text content of the elements
        xpath_query = f"./student[username/text()='{username}' and password/text()='{password}']"
        
        # Find the student element
        student_element = root.xpath(xpath_query)
        
        # If no student found, return None
        if not student_element:
            return None
        
        # Take the first matching student (assuming unique username/password)
        student = student_element[0]
        
        # Extract information from the student element
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text
        
        return student_info
        
    except etree.XMLSyntaxError:
        # Handle invalid XML data
        return None
    except Exception:
        # Handle any other unexpected errors
        return None