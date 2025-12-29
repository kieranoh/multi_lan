const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Przeanalizuj dane XML i zwróć informacje o studencie dla podanej nazwy użytkownika i hasła. Dane XML będą miały następującą strukturę:
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
 * Ładujemy dane XML za pomocą JSDOM(xml_data, { contentType: "application/xml" })
 * Możemy skonstruować zapytanie XPath i użyć go do wyszukiwania.
 *
 * @param {string} xml_data - Dane XML zawierające informacje o studentach.
 * @param {string} username - Nazwa użytkownika studenta, którego szukamy.
 * @param {string} password - Hasło studenta, którego szukamy.
 * @returns {Object|null} Obiekt zawierający informacje o studencie (z właściwościami name, age, citizenship), jeśli student zostanie znaleziony z podaną nazwą użytkownika i hasłem. W przeciwnym razie zwróć null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;
    const xpathExpr = `//student[username="${username}" and password="${password}"]`;
    const studentNode = xpath.select(xpathExpr, doc);

    if (studentNode.length > 0) {
        const student = studentNode[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent,
        };
    }

    return null;
}