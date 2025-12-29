const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XMLデータを解析し、指定されたユーザー名とパスワードに対する学生情報を返します。XMLデータは以下の構造を持っています：
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>John Doe</name>
 *         <citizenship>USA</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>Bob Smith</name>
 *         <citizenship>Canada</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 *
 * JSDOM(xml_data, { contentType: "application/xml" })を使用してXMLデータを読み込みます。
 * XPathクエリを構築し、それを使用して検索できます。
 *
 * @param {string} xml_data - 学生情報を含むXMLデータ。
 * @param {string} username - 検索する学生のユーザー名。
 * @param {string} password - 検索する学生のパスワード。
 * @returns {Object|null} 指定されたユーザー名とパスワードで学生が見つかった場合、学生情報（name、age、citizenshipプロパティを含む）を持つオブジェクトを返します。そうでない場合はnullを返します。
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `/students/student[username='${username}' and password='${password}']`;
    const studentNode = xpath.select(xpathQuery, doc)[0];

    if (studentNode) {
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: parseInt(studentNode.getElementsByTagName('age')[0].textContent, 10),
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent
        };
    }

    return null;
}