const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analyser les données XML et retourner les informations de l'étudiant pour le nom d'utilisateur et le mot de passe donnés.
 * @param {string} xml_data - Les données XML contenant les informations de l'étudiant.
 * @param {string} username - Le nom d'utilisateur de l'étudiant à rechercher.
 * @param {string} password - Le mot de passe de l'étudiant à rechercher.
 * @returns {Object|null} Un objet contenant les informations de l'étudiant (avec les propriétés name, age, citizenship) si l'étudiant est trouvé avec le nom d'utilisateur et le mot de passe donnés. Sinon, retourner null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Charger le document XML avec JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const doc = dom.window.document;
        
        // Construire la requête XPath pour trouver l'élément student correspondant
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // Sélectionner le nœud student correspondant
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, doc)[0];
        
        // Si aucun étudiant n'est trouvé, retourner null
        if (!studentNode) {
            return null;
        }
        
        // Extraire les informations de l'étudiant
        const nameNode = select('name/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        
        // Vérifier que toutes les informations nécessaires sont présentes
        if (!nameNode || !ageNode || !citizenshipNode) {
            return null;
        }
        
        // Convertir l'âge en nombre
        const age = parseInt(ageNode.nodeValue, 10);
        
        // Retourner l'objet avec les informations de l'étudiant
        return {
            name: nameNode.nodeValue,
            age: isNaN(age) ? null : age,
            citizenship: citizenshipNode.nodeValue
        };
    } catch (error) {
        // En cas d'erreur (XML invalide, etc.), retourner null
        return null;
    }
}