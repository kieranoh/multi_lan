from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """XMLデータを解析し、指定されたユーザー名とパスワードに対する学生情報を返します。XMLデータは以下の構造を持っています：
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

XPathクエリを構築し、それを使用して検索できます。


Args:
    xml_data: 学生情報を含むXMLデータ。
    username: 検索する学生のユーザー名
    password: 検索する学生のパスワード

Returns:
    Dict[str, str] | None: 指定されたユーザー名とパスワードで学生が見つかった場合、その学生情報を含む辞書を返します。そうでない場合はNoneを返します。"""
    try:
        # XMLデータをパース
        root = etree.fromstring(xml_data.encode('utf-8'))
        
        # 指定されたユーザー名とパスワードに一致するstudent要素を検索するXPathクエリ
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # 学生が見つからない場合はNoneを返す
        if not student_element:
            return None
        
        # 最初に一致した学生要素を取得
        student = student_element[0]
        
        # 学生情報を辞書に抽出
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        return student_info
        
    except etree.XMLSyntaxError:
        # XMLの構文エラーが発生した場合はNoneを返す
        return None
    except Exception:
        # その他のエラーが発生した場合もNoneを返す
        return None