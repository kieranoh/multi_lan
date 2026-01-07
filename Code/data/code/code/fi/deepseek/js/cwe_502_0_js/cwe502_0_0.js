const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Tarkistetaan, että polku on annettu
        if (!yamlFilePath || typeof yamlFilePath !== 'string') {
            return 'Virhe: YAML-tiedoston polku puuttuu tai on virheellinen.';
        }

        // Luetaan YAML-tiedoston sisältö
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Tarkistetaan, että tiedosto ei ole tyhjä
        if (!yamlContent.trim()) {
            return 'Virhe: YAML-tiedosto on tyhjä.';
        }

        // Muunnetaan YAML JSON-muotoon
        const parsedData = yaml.load(yamlContent);
        
        // Muunnetaan JSON-merkkijonoksi
        const jsonString = JSON.stringify(parsedData, null, 2);
        
        return jsonString;
        
    } catch (error) {
        // Käsitellään erilaiset virhetilanteet
        if (error.code === 'ENOENT') {
            return `Virhe: Tiedostoa ei löydy polusta '${yamlFilePath}'.`;
        } else if (error instanceof yaml.YAMLException) {
            return `Virhe: Virheellinen YAML-sisältö: ${error.message}`;
        } else if (error instanceof SyntaxError) {
            return `Virhe: JSON-muunnos epäonnistui: ${error.message}`;
        } else {
            return `Virhe: ${error.message}`;
        }
    }
}