const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analizza i dati XML e restituisci le informazioni dello studente per il nome utente e la password forniti.
 * @param {string} xml_data - I dati XML contenenti le informazioni dello studente.
 * @param {string} username - Il nome utente dello studente da cercare.
 * @param {string} password - La password dello studente da cercare.
 * @returns {Object|null} Un oggetto contenente le informazioni dello studente (con proprietà nome, età, cittadinanza) se lo studente viene trovato con il nome utente e la password forniti. Altrimenti, restituisci null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Carica il documento XML
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const doc = dom.window.document;
        
        // Costruisci la query XPath per trovare lo studente con username e password corrispondenti
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // Esegui la query XPath
        const select = xpath.useNamespaces({});
        const studentNode = select(query, doc)[0];
        
        // Se non viene trovato alcuno studente, restituisci null
        if (!studentNode) {
            return null;
        }
        
        // Estrai le informazioni dello studente
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // Verifica che tutte le informazioni necessarie siano presenti
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // Costruisci e restituisci l'oggetto con le informazioni dello studente
        return {
            name: nameNode.nodeValue,
            age: parseInt(ageNode.nodeValue, 10),
            citizenship: citizenshipNode.nodeValue
        };
    } catch (error) {
        // In caso di errore (ad esempio XML malformato), restituisci null
        return null;
    }
}