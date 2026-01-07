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
    try {
        // Ladda XML-datan med JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // Skapa XPath-uttryck för att hitta studenten med matchande användarnamn och lösenord
        const select = xpath.useNamespaces({});
        const xpathExpr = `//student[username/text()="${username}" and password/text()="${password}"]`;
        const studentNode = select(xpathExpr, document)[0];

        // Om ingen student hittades, returnera null
        if (!studentNode) {
            return null;
        }

        // Extrahera informationen från studentnoden
        const nameNode = select("name/text()", studentNode)[0];
        const citizenshipNode = select("citizenship/text()", studentNode)[0];
        const ageNode = select("age/text()", studentNode)[0];

        // Skapa och returnera objektet med studentinformation
        return {
            namn: nameNode ? nameNode.nodeValue : null,
            ålder: ageNode ? parseInt(ageNode.nodeValue, 10) : null,
            medborgarskap: citizenshipNode ? citizenshipNode.nodeValue : null
        };
    } catch (error) {
        // Vid fel (t.ex. ogiltig XML), returnera null
        return null;
    }
}