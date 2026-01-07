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
    // Verifica che i parametri siano stringhe non vuote
    if (typeof filename !== 'string' || typeof dir_path !== 'string' || 
        filename.trim() === '' || dir_path.trim() === '') {
        return '';
    }
    
    try {
        // Costruisce il percorso completo del file
        const filePath = path.join(dir_path, filename);
        
        // Legge il contenuto del file in modo sincrono con codifica UTF-8
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // Gestisce tutti gli errori (file non trovato, permessi, ecc.)
        return '';
    }
}