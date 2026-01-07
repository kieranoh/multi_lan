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
    try {
        // Tải XML với JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // Xây dựng truy vấn XPath để tìm student với username và password phù hợp
        const xpathQuery = `//student[username/text()="${username}" and password/text()="${password}"]`;
        
        // Sử dụng xpath.select để tìm node
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // Nếu không tìm thấy student, trả về null
        if (!studentNode) {
            return null;
        }
        
        // Trích xuất thông tin từ node student
        const nameNode = select("name/text()", studentNode)[0];
        const citizenshipNode = select("citizenship/text()", studentNode)[0];
        const ageNode = select("age/text()", studentNode)[0];
        
        // Kiểm tra xem tất cả các trường cần thiết có tồn tại không
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // Chuyển đổi age sang số
        const age = parseInt(ageNode.nodeValue, 10);
        
        // Trả về đối tượng thông tin sinh viên
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: isNaN(age) ? null : age
        };
        
    } catch (error) {
        // Xử lý lỗi nếu có (ví dụ: XML không hợp lệ)
        console.error("Error parsing XML or executing XPath:", error);
        return null;
    }
}

module.exports = { getStudentInfo };