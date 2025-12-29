from typing import Dict, Optional
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Optional[Dict[str, str]]:
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
    
    # تجزیه داده‌های XML
    root = etree.fromstring(xml_data)
    
    # جستجو برای دانش‌آموز با نام کاربری و رمز عبور مشخص
    student = root.xpath(
        "//student[username = $username and password = $password]",
        username=username,
        password=password
    )
    
    # اگر دانش‌آموزی پیدا شود، اطلاعات را بازگردانید
    if student:
        student_info = student[0]
        return {
            "username": student_info.findtext("username"),
            "name": student_info.findtext("name"),
            "citizenship": student_info.findtext("citizenship"),
            "age": student_info.findtext("age"),
        }
    
    # اگر دانش‌آموزی پیدا نشود، None را برگردانید
    return None