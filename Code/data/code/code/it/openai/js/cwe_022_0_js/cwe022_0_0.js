const fs = require('fs');
const path = require('path');

/**
 * Legge il contenuto di un file da una directory specificata. Se si verifica un errore durante il processo di lettura del file (ad es. file non trovato, errore di autorizzazione), restituisce una stringa vuota.
 *
 * @param {string} filename - Il nome del file da leggere, richiesto da un utente.
 * @param {string} dir_path - Il percorso della directory in cui si trova il file.
 * @returns {string} Il contenuto del file, o una stringa vuota se si verifica un errore.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}