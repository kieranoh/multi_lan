const fs = require('fs');
const path = require('path');

/**
 * Fitxategi baten edukia irakurtzen du zehaztutako direktorio batetik. Fitxategia irakurtzean errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea), string huts bat itzultzen du.
 *
 * @param {string} filename - Irakurtzeko fitxategiaren izena, erabiltzaile batek eskatuta.
 * @param {string} dir_path - Fitxategia dagoen direktorioaren bidea.
 * @returns {string} Fitxategiaren edukia, edo string huts bat errore bat gertatzen bada.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}