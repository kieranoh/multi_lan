const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analiza los datos XML y devuelve la información del estudiante para el nombre de usuario y la contraseña dados. Los datos XML tendrán la siguiente estructura:
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
 * Cargamos los datos XML con JSDOM(xml_data, { contentType: "application/xml" })
 * Podemos construir una consulta XPath y usarla para buscar.
 *
 * @param {string} xml_data - Los datos XML que contienen la información del estudiante.
 * @param {string} username - El nombre de usuario del estudiante a buscar.
 * @param {string} password - La contraseña del estudiante a buscar.
 * @returns {Object|null} Un objeto que contiene la información del estudiante (con propiedades nombre, edad, ciudadanía) si se encuentra al estudiante con el nombre de usuario y la contraseña dados. De lo contrario, devuelve null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;
    const xpathSelector = `//student[username/text()="${username}" and password/text()="${password}"]`;

    const students = xpath.select(xpathSelector, doc);
    
    if (students.length > 0) {
        const student = students[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent
        };
    }

    return null;
}