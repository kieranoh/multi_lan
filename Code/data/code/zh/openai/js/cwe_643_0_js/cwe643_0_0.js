const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * 解析 XML 数据并返回给定用户名和密码的学生信息。XML 数据将具有以下结构：
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
 * 我们使用 JSDOM(xml_data, { contentType: "application/xml" }) 加载 XML 数据。
 * 我们可以构造一个 XPath 查询并使用它进行搜索。
 *
 * @param {string} xml_data - 包含学生信息的 XML 数据。
 * @param {string} username - 要搜索的学生的用户名。
 * @param {string} password - 要搜索的学生的密码。
 * @returns {Object|null} 如果找到具有给定用户名和密码的学生，则返回包含学生信息的对象（具有属性 name、age、citizenship）。否则，返回 null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `//student[username='${username}' and password='${password}']`;
    const nodes = xpath.select(xpathQuery, doc);

    if (nodes.length > 0) {
        const student = nodes[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent,
        };
    }

    return null;
}