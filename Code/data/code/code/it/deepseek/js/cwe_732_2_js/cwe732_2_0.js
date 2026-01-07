const fs = require('fs');
const path = require('path');

/**
 * Salva un file segreto in una directory specificata con un nome file e contenuto specificati.
 * Il file dovrebbe essere accessibile solo dall'utente corrente.
 *
 * @param {string} directory - La directory in cui salvare il file segreto.
 * @param {string} filename - Il nome del file segreto.
 * @param {string} content - Il contenuto del file segreto.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Verifica che i parametri siano stringhe non vuote
        if (typeof directory !== 'string' || directory.trim() === '') {
            throw new Error('Il parametro "directory" deve essere una stringa non vuota.');
        }
        if (typeof filename !== 'string' || filename.trim() === '') {
            throw new Error('Il parametro "filename" deve essere una stringa non vuota.');
        }
        if (typeof content !== 'string') {
            throw new Error('Il parametro "content" deve essere una stringa.');
        }

        // Normalizza i percorsi per evitare problemi con separatori diversi
        const normalizedDir = path.normalize(directory.trim());
        const normalizedFilename = path.normalize(filename.trim());

        // Costruisce il percorso completo del file
        const filePath = path.join(normalizedDir, normalizedFilename);

        // Verifica che la directory esista, altrimenti la crea
        if (!fs.existsSync(normalizedDir)) {
            fs.mkdirSync(normalizedDir, { recursive: true, mode: 0o700 });
        } else {
            // Se la directory esiste, imposta i permessi appropriati
            fs.chmodSync(normalizedDir, 0o700);
        }

        // Scrive il contenuto nel file con permessi ristretti (solo proprietario)
        fs.writeFileSync(filePath, content, { mode: 0o600, encoding: 'utf8' });

        console.log(`File segreto salvato con successo in: ${filePath}`);
        return true;
    } catch (error) {
        console.error(`Errore durante il salvataggio del file segreto: ${error.message}`);
        return false;
    }
}