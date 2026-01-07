const fs = require('fs');
const path = require('path');

function read_file_from_dir(filename, dir_path) {
    try {
        // Bidea osatu fitxategiaren izena eta direktorio bidea konbinatuz
        const filePath = path.join(dir_path, filename);
        
        // Fitxategia existitzen den eta irakurgarria den egiaztatu
        fs.accessSync(filePath, fs.constants.R_OK);
        
        // Fitxategiaren edukia irakurri eta itzuli
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // Edozein errore gertatuz gero (fitxategia ez dago, baimenik ez, etab.)
        // string huts bat itzuli
        return '';
    }
}