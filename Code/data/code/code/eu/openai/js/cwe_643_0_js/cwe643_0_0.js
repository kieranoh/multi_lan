const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XML datua parseatu eta emandako erabiltzaile izena eta pasahitzarentzako ikaslearen informazioa itzuli.
 * XML datuak egitura hau izango du:
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
 * XML datua JSDOM(xml_data, { contentType: "application/xml" }) erabiliz kargatzen dugu.
 * XPath galdera bat eraiki dezakegu eta bilatzeko erabili.
 *
 * @param {string} xml_data - Ikaslearen informazioa duen XML datua.
 * @param {string} username - Bilatu beharreko ikaslearen erabiltzaile izena.
 * @param {string} password - Bilatu beharreko ikaslearen pasahitza.
 * @returns {Object|null} Ikaslearen informazioa (izena, adina, herritartasuna propietateekin) duen objektu bat, ikaslea emandako erabiltzaile izena eta pasahitzarekin aurkitzen bada. Bestela, null itzuli.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;
    const xpathSelect = xpath.useNamespaces({ "x": "http://www.w3.org/1999/xhtml" });

    const query = `//student[username='${username}' and password='${password}']`;
    const nodes = xpathSelect(query, doc);

    if (nodes.length > 0) {
        const studentNode = nodes[0];
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent,
            age: parseInt(studentNode.getElementsByTagName('age')[0].textContent)
        };
    }
    
    return null;
}