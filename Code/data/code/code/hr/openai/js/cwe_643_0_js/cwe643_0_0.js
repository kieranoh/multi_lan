const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parsirajte XML podatke i vratite informacije o studentu za zadano korisničko ime i lozinku. XML podaci će imati sljedeću strukturu:
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
 * Učitavamo XML podatke s JSDOM(xml_data, { contentType: "application/xml" })
 * Možemo konstruirati XPath upit i koristiti ga za pretraživanje.
 *
 * @param {string} xml_data - XML podaci koji sadrže informacije o studentu.
 * @param {string} username - Korisničko ime studenta kojeg tražimo.
 * @param {string} password - Lozinka studenta kojeg tražimo.
 * @returns {Object|null} Objekt koji sadrži informacije o studentu (s svojstvima name, age, citizenship) ako je student pronađen s danim korisničkim imenom i lozinkom. Inače, vraća null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `//student[username='${username}' and password='${password}']`;
    const nodes = xpath.select(xpathQuery, doc);

    if (nodes.length > 0) {
        const studentNode = nodes[0];
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: parseInt(studentNode.getElementsByTagName('age')[0].textContent, 10),
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent
        };
    }

    return null;
}