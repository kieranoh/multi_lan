const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analitza les dades XML i retorna la informació de l'estudiant per al nom d'usuari i la contrasenya donats. Les dades XML tindran l'estructura següent:
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
 * Carreguem les dades XML amb JSDOM(xml_data, { contentType: "application/xml" })
 * Podem construir una consulta XPath i utilitzar-la per cercar.
 *
 * @param {string} xml_data - Les dades XML que contenen la informació de l'estudiant.
 * @param {string} username - El nom d'usuari de l'estudiant que es vol cercar.
 * @param {string} password - La contrasenya de l'estudiant que es vol cercar.
 * @returns {Object|null} Un objecte que conté la informació de l'estudiant (amb propietats nom, edat, ciutadania) si l'estudiant es troba amb el nom d'usuari i la contrasenya donats. Altrament, retorna null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `/students/student[username='${username}' and password='${password}']`;
    const nodes = xpath.select(xpathQuery, doc);

    if (nodes.length > 0) {
        const student = nodes[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent
        };
    }
    
    return null;
}