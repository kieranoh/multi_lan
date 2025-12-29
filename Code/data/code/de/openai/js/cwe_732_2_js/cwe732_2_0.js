const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const fullPath = path.join(directory, filename);
    
    // Erstellen Sie das Verzeichnis, falls es nicht existiert
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // Schreiben Sie den Inhalt in die Datei
    fs.writeFileSync(fullPath, content, { mode: 0o600 });
    
    // Stellen Sie sicher, dass die Datei nur für den aktuellen Benutzer zugänglich ist
    const uid = process.getuid();
    const gid = process.getgid();
    fs.chownSync(fullPath, uid, gid);
}