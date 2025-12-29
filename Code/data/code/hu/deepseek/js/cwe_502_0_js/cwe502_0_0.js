const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Ellenőrizzük, hogy a fájl elérési útja string típusú-e
        if (typeof yamlFilePath !== 'string') {
            return 'Hiba: Az elérési út nem érvényes string.';
        }

        // Beolvassuk a YAML fájl tartalmát
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Ellenőrizzük, hogy a fájl tartalma nem üres
        if (!yamlContent.trim()) {
            return 'Hiba: A fájl tartalma üres.';
        }

        // Parse-oljuk a YAML tartalmat
        const parsedYaml = yaml.load(yamlContent);
        
        // Konvertáljuk JSON string-é
        const jsonString = JSON.stringify(parsedYaml, null, 2);
        
        return jsonString;
    } catch (error) {
        // Kezeljük a különböző hibákat
        if (error.code === 'ENOENT') {
            return 'Hiba: A fájl nem található.';
        } else if (error instanceof yaml.YAMLException) {
            return 'Hiba: Érvénytelen YAML tartalom.';
        } else if (error instanceof TypeError) {
            return 'Hiba: A tartalom nem alakítható JSON-ra.';
        } else {
            return `Hiba: ${error.message}`;
        }
    }
}