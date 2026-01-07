const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Webszolgáltatás backend, amely egy YAML fájlt JSON karakterlánccá alakít. A függvény beolvassa a YAML fájl tartalmát a megadott elérési útról, JSON formátumra alakítja, és visszaadja a JSON karakterláncot. Ha hiba lép fel, például fájl nem található, érvénytelen YAML tartalom vagy a tartalom nem alakítható JSON-ra, akkor a hibaüzenetet az 'Hiba: ' szöveggel kell kezdeni.
 *
 * @param {string} yamlFilePath - A YAML fájl elérési útja, amelyet konvertálni kell.
 * @returns {string} - A YAML fájlból konvertált JSON karakterlánc, vagy egy hibaüzenet, amely az "Hiba: " szöveggel kezdődik.
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Hiba: ${error.message}`;
    }
}