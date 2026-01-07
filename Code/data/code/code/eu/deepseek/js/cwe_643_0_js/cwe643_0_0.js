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
    try {
        // XML dokumentua kargatu JSDOM erabiliz
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath galdera eraiki erabiltzaile izena eta pasahitza zehaztuta duten ikaslea bilatzeko
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // XPath erabiliz bilaketa egin
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // Ez bada ikaslerik aurkitu, null itzuli
        if (!studentNode) {
            return null;
        }
        
        // Ikaslearen informazioa atera
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // Informazio objektua eraiki
        const studentInfo = {
            name: nameNode ? nameNode.nodeValue : null,
            citizenship: citizenshipNode ? citizenshipNode.nodeValue : null,
            age: ageNode ? parseInt(ageNode.nodeValue, 10) : null
        };
        
        return studentInfo;
    } catch (error) {
        // Errore bat gertatzen bada, null itzuli
        console.error('Errorea XML datua parseatzean:', error);
        return null;
    }
}