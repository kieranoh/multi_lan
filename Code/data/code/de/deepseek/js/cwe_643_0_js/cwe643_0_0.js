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
    try {
        // XML-Dokument mit JSDOM laden
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath-Abfrage konstruieren, um den Schüler mit dem angegebenen Benutzernamen und Passwort zu finden
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // XPath-Auswertung durchführen
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // Wenn kein Schüler gefunden wurde, null zurückgeben
        if (!studentNode) {
            return null;
        }
        
        // Informationen aus dem gefundenen Schülerknoten extrahieren
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // Überprüfen, ob alle erforderlichen Informationen vorhanden sind
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // Objekt mit den Schülerinformationen erstellen und zurückgeben
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: parseInt(ageNode.nodeValue, 10)
        };
    } catch (error) {
        // Bei einem Fehler (z.B. ungültiges XML) null zurückgeben
        return null;
    }
}