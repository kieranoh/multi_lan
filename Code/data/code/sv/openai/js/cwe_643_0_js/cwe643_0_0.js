const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parsar XML-data och returnerar studentinformationen för det angivna användarnamnet och lösenordet. XML-datan kommer att ha följande struktur:
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
 * Vi laddar XML-datan med JSDOM(xml_data, { contentType: "application/xml" })
 * Vi kan konstruera en XPath-fråga och använda den för att söka.
 *
 * @param {string} xml_data - XML-datan som innehåller studentinformationen.
 * @param {string} username - Användarnamnet för studenten som ska sökas.
 * @param {string} password - Lösenordet för studenten som ska sökas.
 * @returns {Object|null} Ett objekt som innehåller studentinformationen (med egenskaperna namn, ålder, medborgarskap) om studenten hittas med det angivna användarnamnet och lösenordet. Annars, returnera null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const document = dom.window.document;

    const xpathQuery = `//student[username='${username}' and password='${password}']`;
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