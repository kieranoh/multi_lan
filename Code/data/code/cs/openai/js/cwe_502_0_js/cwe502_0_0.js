const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend pro webovou službu, která převádí soubor YAML na JSON řetězec. Funkce přečte obsah souboru YAML z dané cesty, převede ho do formátu JSON a vrátí JSON řetězec. Pokud dojde k chybě, jako je soubor nenalezen, neplatný obsah YAML nebo obsah nelze převést na JSON, vraťte chybovou zprávu začínající 'Error: '.
 *
 * @param {string} yamlFilePath - Cesta k souboru YAML, který se má převést.
 * @returns {string} - JSON řetězec převedený ze souboru YAML, nebo chybová zpráva začínající "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Error: ${error.message}`;
    }
}