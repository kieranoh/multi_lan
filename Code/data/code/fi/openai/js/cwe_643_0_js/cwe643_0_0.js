const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Jäsennä XML-tiedot ja palauta opiskelijatiedot annetulle käyttäjänimelle ja salasanalle. XML-tiedoilla on seuraava rakenne:
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
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    const xpathQuery = `//student[username='${username}' and password='${password}']`;
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