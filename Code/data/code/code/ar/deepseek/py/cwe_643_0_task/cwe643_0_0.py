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
    try:
        # تحليل بيانات XML
        root = etree.fromstring(xml_data.encode('utf-8') if isinstance(xml_data, str) else xml_data)
        
        # بناء استعلام XPath للبحث عن الطالب الذي يطابق اسم المستخدم وكلمة المرور
        xpath_query = f"//student[username='{username}' and password='{password}']"
        
        # البحث عن عنصر الطالب
        student_element = root.xpath(xpath_query)
        
        # إذا لم يتم العثور على الطالب
        if not student_element:
            return None
        
        # استخراج معلومات الطالب من العنصر الأول (يجب أن يكون هناك طالب واحد فقط)
        student = student_element[0]
        
        # استخراج جميع العناصر الفرعية وتحويلها إلى قاموس
        student_info = {}
        for child in student:
            tag_name = child.tag
            text_content = child.text.strip() if child.text else ""
            student_info[tag_name] = text_content
        
        # إزالة اسم المستخدم وكلمة المرور من النتيجة إذا لزم الأمر
        # (يمكن الاحتفاظ بهما إذا كان مطلوبًا في القاموس)
        
        return student_info
        
    except etree.XMLSyntaxError:
        # في حالة وجود خطأ في بناء جملة XML
        return None
    except Exception as e:
        # معالجة أي استثناءات أخرى
        return None