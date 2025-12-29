const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Zpracujte XML data a vraťte informace o studentovi pro zadané uživatelské jméno a heslo. XML data budou mít následující strukturu:
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
 * Načteme XML data pomocí JSDOM(xml_data, { contentType: "application/xml" })
 * Můžeme sestavit dotaz XPath a použít ho k vyhledávání.
 *
 * @param {string} xml_data - XML data obsahující informace o studentech.
 * @param {string} username - Uživatelské jméno studenta, kterého hledáme.
 * @param {string} password - Heslo studenta, kterého hledáme.
 * @returns {Object|null} Objekt obsahující informace o studentovi (s vlastnostmi name, age, citizenship), pokud je student nalezen se zadaným uživatelským jménem a heslem. Jinak vraťte null.
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