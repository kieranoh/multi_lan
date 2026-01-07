const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Elemezze az XML adatokat, és adja vissza a hallgatói információkat a megadott felhasználónév és jelszó alapján.
 * @param {string} xml_data - Az XML adat, amely a hallgatói információkat tartalmazza.
 * @param {string} username - A keresett hallgató felhasználóneve.
 * @param {string} password - A keresett hallgató jelszava.
 * @returns {Object|null} Egy objektum, amely a hallgatói információkat tartalmazza (név, életkor, állampolgárság tulajdonságokkal), ha a hallgató megtalálható a megadott felhasználónévvel és jelszóval. Ellenkező esetben nullát ad vissza.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // XML dokumentum betöltése JSDOM segítségével
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath kifejezés a megfelelő hallgató megtalálásához
        const xpathExpression = `//student[username/text()="${username}" and password/text()="${password}"]`;
        
        // XPath kiértékelő létrehozása
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathExpression, document)[0];
        
        // Ha nem található hallgató, null visszaadása
        if (!studentNode) {
            return null;
        }
        
        // Hallgató adatainak kinyerése
        const nameNode = select("name/text()", studentNode)[0];
        const citizenshipNode = select("citizenship/text()", studentNode)[0];
        const ageNode = select("age/text()", studentNode)[0];
        
        // Ha bármelyik szükséges adat hiányzik, null visszaadása
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // Életkor számként konvertálása
        const age = parseInt(ageNode.nodeValue, 10);
        
        // Eredmény objektum összeállítása
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: isNaN(age) ? null : age
        };
        
    } catch (error) {
        // Hiba esetén null visszaadása
        console.error("Hiba az XML feldolgozása során:", error.message);
        return null;
    }
}