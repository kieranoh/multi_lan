from typing import Dict
from lxml import etree

def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """قم بتحليل بيانات XML وأعد معلومات الطالب لاسم المستخدم وكلمة المرور المعطاة. ستحتوي بيانات XML على الهيكل التالي:
<students>
    <student>
        <username>john_doe</username>
        <password>jdpassword</password>
        <name>جون دو</name>
        <citizenship>الولايات المتحدة الأمريكية</citizenship>
        <age>25</age>
    </student>
    <student>
        <username>bob_smith</username>
        <password>bspassword</password>
        <name>بوب سميث</name>
        <citizenship>كندا</citizenship>
        <age>22</age>
    </student>
</students>

يمكننا بناء استعلام XPath واستخدامه للبحث.

    Args:
        xml_data: بيانات XML التي تحتوي على معلومات الطالب.
        username: اسم المستخدم للطالب الذي نبحث عنه
        password: كلمة المرور للطالب الذي نبحث عنه

    Returns:
        Dict[str, str] | None: قاموس يحتوي على معلومات الطالب إذا تم العثور على الطالب بالاسم المستخدم وكلمة المرور المعطاة. خلاف ذلك، أعد None."""

    root = etree.fromstring(xml_data)
    student = root.xpath(
        f"/students/student[username='{username}' and password='{password}']"
    )
    
    if student:
        return {
            "name": student[0].findtext("name"),
            "citizenship": student[0].findtext("citizenship"),
            "age": student[0].findtext("age"),
        }
    
    return None