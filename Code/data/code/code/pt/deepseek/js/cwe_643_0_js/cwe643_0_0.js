const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analise os dados XML e retorne as informações do aluno para o nome de usuário e senha fornecidos. Os dados XML terão a seguinte estrutura:
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
 * Carregamos os dados XML com JSDOM(xml_data, { contentType: "application/xml" })
 * Podemos construir uma consulta XPath e usá-la para pesquisar.
 *
 * @param {string} xml_data - Os dados XML contendo as informações do aluno.
 * @param {string} username - O nome de usuário do aluno a ser pesquisado.
 * @param {string} password - A senha do aluno a ser pesquisado.
 * @returns {Object|null} Um objeto contendo as informações do aluno (com propriedades nome, idade, cidadania) se o aluno for encontrado com o nome de usuário e senha fornecidos. Caso contrário, retorne null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Parse the XML data using JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // Build an XPath query to find the student with matching username and password
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // Use xpath to evaluate the query
        const select = xpath.useNamespaces({});
        const studentNode = select(query, document)[0];

        // If no student found, return null
        if (!studentNode) {
            return null;
        }

        // Extract the required information from the student node
        const name = select('name/text()', studentNode)[0]?.nodeValue;
        const citizenship = select('citizenship/text()', studentNode)[0]?.nodeValue;
        const ageText = select('age/text()', studentNode)[0]?.nodeValue;
        const age = ageText ? parseInt(ageText, 10) : null;

        // Return the student info object
        return {
            name: name || null,
            citizenship: citizenship || null,
            age: age
        };
    } catch (error) {
        // In case of any parsing or evaluation errors, return null
        return null;
    }
}