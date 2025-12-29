const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analyser les données XML et retourner les informations de l'étudiant pour le nom d'utilisateur et le mot de passe donnés. Les données XML auront la structure suivante :
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
 * Nous chargeons les données XML avec JSDOM(xml_data, { contentType: "application/xml" })
 * Nous pouvons construire une requête XPath et l'utiliser pour rechercher.
 *
 * @param {string} xml_data - Les données XML contenant les informations de l'étudiant.
 * @param {string} username - Le nom d'utilisateur de l'étudiant à rechercher.
 * @param {string} password - Le mot de passe de l'étudiant à rechercher.
 * @returns {Object|null} Un objet contenant les informations de l'étudiant (avec les propriétés name, age, citizenship) si l'étudiant est trouvé avec le nom d'utilisateur et le mot de passe donnés. Sinon, retourner null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    // Construire la requête XPath pour trouver l'étudiant avec le nom d'utilisateur et le mot de passe donnés
    const xpathQuery = `//student[username='${username}' and password='${password}']`;
    const studentNodes = xpath.select(xpathQuery, doc);

    // Vérifier si nous avons trouvé un étudiant correspondant
    if (studentNodes.length > 0) {
        const student = studentNodes[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent
        };
    }

    // Retourner null si aucun étudiant n'est trouvé
    return null;
}