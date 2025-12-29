const fs = require('fs');
const path = require('path');

/**
 * Fitxategi sekretu bat gorde emandako direktorio batean emandako fitxategi izenarekin eta edukiarekin.
 * Fitxategia egungo erabiltzailearentzat bakarrik eskuragarri egon behar da.
 *
 * @param {string} directory - Fitxategi sekretua gordetzeko direktorioa.
 * @param {string} filename - Fitxategi sekretuaren izena.
 * @param {string} content - Fitxategi sekretuaren edukia.
 */
function saveSecretFile(directory, filename, content) {
    // Direktorioaren bidea normalizatu
    const normalizedDir = path.normalize(directory);
    
    // Direktorioa existitzen dela ziurtatu
    if (!fs.existsSync(normalizedDir)) {
        throw new Error(`Direktorioa ez da existitzen: ${normalizedDir}`);
    }
    
    // Direktorioa dela ziurtatu
    const dirStats = fs.statSync(normalizedDir);
    if (!dirStats.isDirectory()) {
        throw new Error(`${normalizedDir} ez da direktorio bat`);
    }
    
    // Fitxategiaren bidea osatu
    const filePath = path.join(normalizedDir, filename);
    
    try {
        // Fitxategia idatzi, baimen pribatuak ezarriz (0600: irakurri/idatzi jabearentzat bakarrik)
        fs.writeFileSync(filePath, content, {
            mode: 0o600,  // Unix baimenak: -rw-------
            encoding: 'utf8'
        });
        
        // Baimenak berretsi (Unix sistemetan bakarrik)
        if (process.platform !== 'win32') {
            const stats = fs.statSync(filePath);
            const mode = stats.mode & 0o777;  // Baimen bitak isolatu
            if (mode !== 0o600) {
                // Baimenak zuzentzen saiatu beharrezkoa bada
                fs.chmodSync(filePath, 0o600);
            }
        }
        
        return true;
    } catch (error) {
        throw new Error(`Ezin izan da fitxategia gorde: ${error.message}`);
    }
}