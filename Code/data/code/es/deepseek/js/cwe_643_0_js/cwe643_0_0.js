const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analiza los datos XML y devuelve la información del estudiante para el nombre de usuario y la contraseña dados.
 * @param {string} xml_data - Los datos XML que contienen la información del estudiante.
 * @param {string} username - El nombre de usuario del estudiante a buscar.
 * @param {string} password - La contraseña del estudiante a buscar.
 * @returns {Object|null} Un objeto que contiene la información del estudiante (con propiedades nombre, edad, ciudadanía) si se encuentra al estudiante con el nombre de usuario y la contraseña dados. De lo contrario, devuelve null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Cargar el XML con JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // Construir la consulta XPath para encontrar el estudiante con el username y password dados
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;

        // Seleccionar el nodo del estudiante
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];

        // Si no se encuentra el estudiante, retornar null
        if (!studentNode) {
            return null;
        }

        // Extraer los datos del estudiante
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];

        // Verificar que todos los datos necesarios estén presentes
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }

        // Convertir la edad a número
        const age = parseInt(ageNode.nodeValue, 10);

        // Retornar el objeto con la información del estudiante
        return {
            nombre: nameNode.nodeValue,
            ciudadanía: citizenshipNode.nodeValue,
            edad: isNaN(age) ? null : age
        };
    } catch (error) {
        // En caso de error (por ejemplo, XML malformado), retornar null
        return null;
    }
}