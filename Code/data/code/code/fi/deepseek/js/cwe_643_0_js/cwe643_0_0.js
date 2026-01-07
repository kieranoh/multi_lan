const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Jäsennä XML-tiedot ja palauta opiskelijatiedot annetulle käyttäjänimelle ja salasanalle.
 * XML-tiedoilla on seuraava rakenne:
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
 * Lataamme XML-tiedot JSDOM(xml_data, { contentType: "application/xml" })
 * Voimme rakentaa XPath-kyselyn ja käyttää sitä hakemiseen.
 *
 * @param {string} xml_data - XML-tiedot, jotka sisältävät opiskelijatiedot.
 * @param {string} username - Opiskelijan käyttäjänimi, jota etsitään.
 * @param {string} password - Opiskelijan salasana, jota etsitään.
 * @returns {Object|null} Objekti, joka sisältää opiskelijatiedot (ominaisuuksilla nimi, ikä, kansalaisuus), jos opiskelija löytyy annetulla käyttäjänimellä ja salasanalla. Muuten palautetaan null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Jäsennä XML-tiedot JSDOM:lla
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // Tarkista, että XML on oikein muotoiltu
        if (!document.documentElement) {
            return null;
        }
        
        // Luo XPath-evaluattori
        const select = xpath.useNamespaces({});
        
        // Luo XPath-kysely, joka etsii opiskelijan annetulla käyttäjänimellä ja salasanalla
        const xpathQuery = `//student[username/text()="${username}" and password/text()="${password}"]`;
        
        // Suorita XPath-kysely
        const studentNode = select(xpathQuery, document)[0];
        
        // Jos opiskelijaa ei löydy, palauta null
        if (!studentNode) {
            return null;
        }
        
        // Hae opiskelijan tiedot
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // Tarkista, että kaikki tarvittavat tiedot ovat saatavilla
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // Muunna ikä numeroksi
        const age = parseInt(ageNode.nodeValue, 10);
        
        // Palauta opiskelijatiedot objektina
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: isNaN(age) ? null : age
        };
        
    } catch (error) {
        // Jos jokin menee pieleen (esim. virheellinen XML), palauta null
        console.error('Virhe XML:n jäsentämisessä:', error.message);
        return null;
    }
}