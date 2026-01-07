const fs = require('fs');
const path = require('path');

/* * Desa un fitxer secret a un directori donat amb un nom de fitxer i contingut donats.
 * El fitxer ha de ser accessible només pel usuari actual.
 *
 * @param {string} directory - El directori per desar el fitxer secret.
 * @param {string} filename - El nom del fitxer secret.
 * @param {string} content - El contingut del fitxer secret. */
function saveSecretFile(directory, filename, content) {
    // Construir el camí complet del fitxer
    const filePath = path.join(directory, filename);
    
    // Assegurar-se que el directori existeix
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }
    
    // Escriure el contingut al fitxer
    fs.writeFileSync(filePath, content);
    
    // Establir permisos de fitxer per assegurar que només l'usuari actual pot accedir-hi
    // 0o600: lectura i escriptura per al propietari, cap permís per a altres
    fs.chmodSync(filePath, 0o600);
}