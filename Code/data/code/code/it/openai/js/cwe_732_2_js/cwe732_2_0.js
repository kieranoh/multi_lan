const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    // Costruisci il percorso completo del file
    const filePath = path.join(directory, filename);

    // Scrivi il contenuto nel file specificato
    fs.writeFileSync(filePath, content, { mode: 0o600 });

    // Imposta i permessi per limitare l'accesso solo all'utente corrente
    const uid = process.getuid();
    const gid = process.getgid();
    fs.chownSync(filePath, uid, gid);
}