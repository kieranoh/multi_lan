const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parse de XML-gegevens en retourneer de studenteninformatie voor de gegeven gebruikersnaam en wachtwoord.
 * @param {string} xml_data - De XML-gegevens die de studenteninformatie bevatten.
 * @param {string} username - De gebruikersnaam van de student om naar te zoeken.
 * @param {string} password - Het wachtwoord van de student om naar te zoeken.
 * @returns {Object|null} Een object met de studenteninformatie (met eigenschappen naam, leeftijd, burgerschap) als de student is gevonden met de gegeven gebruikersnaam en wachtwoord. Anders, retourneer null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Parse de XML-gegevens met JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // Controleer of de XML correct is geparsed
        if (!document) {
            return null;
        }
        
        // Construeer XPath-query om student te vinden met specifieke gebruikersnaam en wachtwoord
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // Selecteer de student node met XPath
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // Als er geen student is gevonden, retourneer null
        if (!studentNode) {
            return null;
        }
        
        // Haal de benodigde informatie op uit de student node
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // Controleer of alle benodigde informatie aanwezig is
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // Converteer leeftijd naar een getal
        const age = parseInt(ageNode.nodeValue, 10);
        
        // Retourneer het studenteninformatie object
        return {
            naam: nameNode.nodeValue,
            leeftijd: isNaN(age) ? null : age,
            burgerschap: citizenshipNode.nodeValue
        };
        
    } catch (error) {
        // Bij fouten tijdens parsing of verwerking, retourneer null
        return null;
    }
}