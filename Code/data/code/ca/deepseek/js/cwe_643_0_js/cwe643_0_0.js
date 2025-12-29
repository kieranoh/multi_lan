const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // Carregar les dades XML amb JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // Construir la consulta XPath per cercar l'estudiant amb el nom d'usuari i contrasenya donats
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        const studentNode = xpath.select(query, document)[0];

        // Si no es troba cap estudiant, retornar null
        if (!studentNode) {
            return null;
        }

        // Extreure les dades de l'estudiant
        const name = xpath.select1("name/text()", studentNode)?.nodeValue;
        const citizenship = xpath.select1("citizenship/text()", studentNode)?.nodeValue;
        const age = xpath.select1("age/text()", studentNode)?.nodeValue;

        // Retornar l'objecte amb la informació de l'estudiant
        return {
            name: name || null,
            citizenship: citizenship || null,
            age: age ? parseInt(age, 10) : null
        };
    } catch (error) {
        // En cas d'error, retornar null
        return null;
    }
}