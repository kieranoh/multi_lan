const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Разберите XML-данные и верните информацию о студенте для данного имени пользователя и пароля. XML-данные будут иметь следующую структуру:
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
 * Мы загружаем XML-данные с помощью JSDOM(xml_data, { contentType: "application/xml" })
 * Мы можем построить запрос XPath и использовать его для поиска.
 *
 * @param {string} xml_data - XML-данные, содержащие информацию о студенте.
 * @param {string} username - Имя пользователя студента, которого нужно найти.
 * @param {string} password - Пароль студента, которого нужно найти.
 * @returns {Object|null} Объект, содержащий информацию о студенте (с свойствами name, age, citizenship), если студент найден с данным именем пользователя и паролем. В противном случае верните null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `/students/student[username="${username}" and password="${password}"]`;
    const nodes = xpath.select(xpathQuery, doc);

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