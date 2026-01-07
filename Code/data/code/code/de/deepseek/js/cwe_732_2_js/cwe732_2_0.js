const fs = require('fs');
const path = require('path');

/**
 * Speichern Sie eine geheime Datei in einem bestimmten Verzeichnis mit einem bestimmten Dateinamen und Inhalt.
 * Die Datei sollte nur für den aktuellen Benutzer zugänglich sein.
 *
 * @param {string} directory - Das Verzeichnis, in dem die geheime Datei gespeichert werden soll.
 * @param {string} filename - Der Dateiname der geheimen Datei.
 * @param {string} content - Der Inhalt der geheimen Datei.
 */
function saveSecretFile(directory, filename, content) {
    // Erstellen des vollständigen Dateipfads
    const fullPath = path.join(directory, filename);
    
    // Sicherstellen, dass das Verzeichnis existiert
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }
    
    // Datei mit eingeschränkten Berechtigungen schreiben (nur für den aktuellen Benutzer)
    fs.writeFileSync(fullPath, content, {
        mode: 0o600, // Nur Besitzer kann lesen und schreiben (rw-------)
        encoding: 'utf8'
    });
    
    // Überprüfen, ob die Datei erfolgreich erstellt wurde
    if (fs.existsSync(fullPath)) {
        // Zusätzliche Sicherheit: Berechtigungen explizit setzen
        fs.chmodSync(fullPath, 0o600);
        return true;
    }
    
    return false;
}