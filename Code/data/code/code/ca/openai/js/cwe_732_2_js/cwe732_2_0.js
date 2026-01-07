const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // Escriure el contingut al fitxer
    fs.writeFileSync(filePath, content);

    // Canviar els permisos del fitxer per fer-lo accessible només pel usuari actual
    const chmod = require('child_process').execSync;
    chmod(`chmod 600 ${filePath}`);
}