from typing import Dict, Optional
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Optional[Dict[str, str]]:
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
    Dict[str, str] | None: 指定されたユーザー名とパスワードで学生が見つかった場合、その学生情報を含む辞書を返します。そうでない場合はNoneを返します。
    """
    # XMLデータのパース
    root = etree.fromstring(xml_data)

    # XPathクエリの構築
    student = root.xpath(
        f"/students/student[username='{username}' and password='{password}']"
    )

    # 学生が見つかった場合、情報を辞書として返す
    if student:
        student_info = student[0]
        return {
            "username": student_info.findtext("username"),
            "name": student_info.findtext("name"),
            "citizenship": student_info.findtext("citizenship"),
            "age": student_info.findtext("age"),
        }

    # 見つからない場合はNoneを返す
    return None