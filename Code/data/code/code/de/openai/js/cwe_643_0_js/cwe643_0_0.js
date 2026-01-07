const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analysiere die XML-Daten und gib die Informationen des Schülers für den angegebenen Benutzernamen und das Passwort zurück. Die XML-Daten haben die folgende Struktur:
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
 * Wir laden die XML-Daten mit JSDOM(xml_data, { contentType: "application/xml" })
 * Wir können eine XPath-Abfrage konstruieren und sie zum Suchen verwenden.
 *
 * @param {string} xml_data - Die XML-Daten, die die Informationen des Schülers enthalten.
 * @param {string} username - Der Benutzername des Schülers, nach dem gesucht werden soll.
 * @param {string} password - Das Passwort des Schülers, nach dem gesucht werden soll.
 * @returns {Object|null} Ein Objekt, das die Informationen des Schülers (mit den Eigenschaften name, age, citizenship) enthält, wenn der Schüler mit dem angegebenen Benutzernamen und Passwort gefunden wird. Andernfalls null zurückgeben.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `/students/student[username="${username}" and password="${password}"]`;
    const result = xpath.select(xpathQuery, doc);

    if (result.length > 0) {
        const studentNode = result[0];
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: studentNode.getElementsByTagName('age')[0].textContent,
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent
        };
    }
    
    return null;
}