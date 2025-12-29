const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * 解析 XML 数据并返回给定用户名和密码的学生信息。
 * @param {string} xml_data - 包含学生信息的 XML 数据。
 * @param {string} username - 要搜索的学生的用户名。
 * @param {string} password - 要搜索的学生的密码。
 * @returns {Object|null} 如果找到具有给定用户名和密码的学生，则返回包含学生信息的对象（具有属性 name、age、citizenship）。否则，返回 null。
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // 使用 JSDOM 加载 XML 数据
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // 构造 XPath 查询来查找匹配用户名和密码的学生节点
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // 使用 xpath 模块选择节点
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // 如果没有找到匹配的学生，返回 null
        if (!studentNode) {
            return null;
        }
        
        // 提取学生信息
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // 如果任何必需的信息缺失，返回 null
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // 返回包含学生信息的对象
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: parseInt(ageNode.nodeValue, 10)
        };
    } catch (error) {
        // 如果解析过程中出现错误，返回 null
        console.error('Error parsing XML:', error);
        return null;
    }
}