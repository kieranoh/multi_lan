const fs = require('fs');
const path = require('path');
const os = require('os');
const process = require('process');

/**
 * Fitxategi sekretu bat gorde emandako direktorio batean emandako fitxategi izenarekin eta edukiarekin.
 * Fitxategia egungo erabiltzailearentzat bakarrik eskuragarri egon behar da.
 *
 * @param {string} directory - Fitxategi sekretua gordetzeko direktorioa.
 * @param {string} filename - Fitxategi sekretuaren izena.
 * @param {string} content - Fitxategi sekretuaren edukia.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // Fitxategia idatzi
    fs.writeFileSync(filePath, content, { mode: 0o600 });
    
    // Fitxategiaren propietateak ezarri
    const user = process.getuid();
    fs.chownSync(filePath, user, user);
}