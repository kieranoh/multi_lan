const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Web zerbitzurako atala, YAML fitxategi bat json kate bihurtzen duena.
 * Funtzioak YAML fitxategiaren edukia emandako bidean irakurtzen du, 
 * JSON formatura bihurtzen du, eta JSON kate itzultzen du. 
 * Akatsik badago, hala nola fitxategia aurkitu ez izana, 
 * YAML edukia baliogabea izatea edo edukia JSON-era bihurtu ezin izatea, 
 * 'Error: ' hasierako akats mezua itzuli.
 *
 * @param {string} yamlFilePath - YAML fitxategiaren bidea.
 * @returns {string} - JSON formatuan irakurtutako edukia edo akats mezua.
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (e) {
        return `Error: ${e.message}`;
    }
}