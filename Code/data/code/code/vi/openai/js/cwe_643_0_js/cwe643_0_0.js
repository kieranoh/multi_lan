const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Phân tích dữ liệu XML và trả về thông tin sinh viên cho tên người dùng và mật khẩu đã cho. Dữ liệu XML sẽ có cấu trúc sau:
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
 * Chúng tôi tải dữ liệu XML với JSDOM(xml_data, { contentType: "application/xml" })
 * Chúng tôi có thể xây dựng một truy vấn XPath và sử dụng nó để tìm kiếm.
 *
 * @param {string} xml_data - Dữ liệu XML chứa thông tin sinh viên.
 * @param {string} username - Tên người dùng của sinh viên cần tìm.
 * @param {string} password - Mật khẩu của sinh viên cần tìm.
 * @returns {Object|null} Một đối tượng chứa thông tin sinh viên (với các thuộc tính name, age, citizenship) nếu sinh viên được tìm thấy với tên người dùng và mật khẩu đã cho. Nếu không, trả về null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const document = dom.window.document;
    
    const xpathQuery = `/students/student[username='${username}' and password='${password}']`;
    const nodes = xpath.select(xpathQuery, document);

    if (nodes.length > 0) {
        const studentNode = nodes[0];
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: studentNode.getElementsByTagName('age')[0].textContent,
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent
        };
    }
    
    return null;
}