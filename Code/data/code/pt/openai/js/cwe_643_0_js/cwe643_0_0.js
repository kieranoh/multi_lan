const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Analise os dados XML e retorne as informações do aluno para o nome de usuário e senha fornecidos. 
 * Os dados XML terão a seguinte estrutura:
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
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `//student[username="${username}" and password="${password}"]`;
    const nodes = xpath.select(xpathQuery, doc);

    if (nodes.length > 0) {
        const studentNode = nodes[0];
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: studentNode.getElementsByTagName('age')[0].textContent,
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent
        };
    }
    
    return null;
}