const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Verkkopalvelun taustajärjestelmä, joka muuntaa YAML-tiedoston JSON-merkkijonoksi. Funktio lukee YAML-tiedoston sisällön annetusta polusta, muuntaa sen JSON-muotoon ja palauttaa JSON-merkkijonon. Jos ilmenee virhe, kuten tiedostoa ei löydy, virheellinen YAML-sisältö tai sisältöä ei voida muuntaa JSON:ksi, palauta virheilmoitus, joka alkaa 'Virhe: '.
 *
 * @param {string} yamlFilePath - Polku muunnettavalle YAML-tiedostolle.
 * @returns {string} - JSON-merkkijono, joka on muunnettu YAML-tiedostosta, tai virheilmoitus, joka alkaa "Virhe: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Virhe: ${error.message}`;
    }
}