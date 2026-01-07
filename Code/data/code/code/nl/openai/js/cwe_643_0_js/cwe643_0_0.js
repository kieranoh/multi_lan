const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parse de XML-gegevens en retourneer de studenteninformatie voor de gegeven gebruikersnaam en wachtwoord. De XML-gegevens hebben de volgende structuur:
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
 * We laden de XML-gegevens met JSDOM(xml_data, { contentType: "application/xml" })
 * We kunnen een XPath-query construeren en deze gebruiken om te zoeken.
 *
 * @param {string} xml_data - De XML-gegevens die de studenteninformatie bevatten.
 * @param {string} username - De gebruikersnaam van de student om naar te zoeken.
 * @param {string} password - Het wachtwoord van de student om naar te zoeken.
 * @returns {Object|null} Een object met de studenteninformatie (met eigenschappen naam, leeftijd, burgerschap) als de student is gevonden met de gegeven gebruikersnaam en wachtwoord. Anders, retourneer null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `//student[username='${username}' and password='${password}']`;
    const studentNode = xpath.select(xpathQuery, doc);

    if (studentNode.length > 0) {
        const student = studentNode[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: parseInt(student.getElementsByTagName('age')[0].textContent, 10),
            citizenship: student.getElementsByTagName('citizenship')[0].textContent
        };
    }
    
    return null;
}