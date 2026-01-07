const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parsirajte XML podatke i vratite informacije o studentu za dati korisničko ime i lozinku. XML podaci će imati sledeću strukturu:
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
 * Učitavamo XML podatke sa JSDOM(xml_data, { contentType: "application/xml" })
 * Možemo konstruisati XPath upit i koristiti ga za pretragu.
 *
 * @param {string} xml_data - XML podaci koji sadrže informacije o studentu.
 * @param {string} username - Korisničko ime studenta koji se traži.
 * @param {string} password - Lozinka studenta koji se traži.
 * @returns {Object|null} Objekat koji sadrži informacije o studentu (sa svojstvima name, age, citizenship) ako je student pronađen sa datim korisničkim imenom i lozinkom. U suprotnom, vraća null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `/students/student[username='${username}' and password='${password}']`;
    const studentNode = xpath.select(xpathQuery, doc)[0];

    if (studentNode) {
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: studentNode.getElementsByTagName('age')[0].textContent,
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent,
        };
    }
    
    return null;
}