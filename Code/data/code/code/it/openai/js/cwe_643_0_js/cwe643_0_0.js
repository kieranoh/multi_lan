const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analizza i dati XML e restituisci le informazioni dello studente per il nome utente e la password forniti. I dati XML avranno la seguente struttura:
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
 * Carichiamo i dati XML con JSDOM(xml_data, { contentType: "application/xml" })
 * Possiamo costruire una query XPath e usarla per cercare.
 *
 * @param {string} xml_data - I dati XML contenenti le informazioni dello studente.
 * @param {string} username - Il nome utente dello studente da cercare.
 * @param {string} password - La password dello studente da cercare.
 * @returns {Object|null} Un oggetto contenente le informazioni dello studente (con proprietà nome, età, cittadinanza) se lo studente viene trovato con il nome utente e la password forniti. Altrimenti, restituisci null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const document = dom.window.document;

    const xpathQuery = `//student[username='${username}' and password='${password}']`;
    const studentNode = xpath.select(xpathQuery, document);

    if (studentNode.length > 0) {
        const student = studentNode[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent
        };
    }

    return null;
}