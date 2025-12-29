const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Elemezze az XML adatokat, és adja vissza a hallgatói információkat a megadott felhasználónév és jelszó alapján. Az XML adatok a következő struktúrával rendelkeznek:
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
 * Az XML adatokat a JSDOM(xml_data, { contentType: "application/xml" }) segítségével töltjük be.
 * Készíthetünk egy XPath lekérdezést, és használhatjuk azt a kereséshez.
 *
 * @param {string} xml_data - Az XML adat, amely a hallgatói információkat tartalmazza.
 * @param {string} username - A keresett hallgató felhasználóneve.
 * @param {string} password - A keresett hallgató jelszava.
 * @returns {Object|null} Egy objektum, amely a hallgatói információkat tartalmazza (név, életkor, állampolgárság tulajdonságokkal), ha a hallgató megtalálható a megadott felhasználónévvel és jelszóval. Ellenkező esetben nullát ad vissza.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;
    const xpathSelect = `//student[username='${username}' and password='${password}']`;
    const results = xpath.select(xpathSelect, doc);

    if (results.length > 0) {
        const student = results[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent
        };
    }

    return null;
}