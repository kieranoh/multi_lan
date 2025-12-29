const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Restituisce l'output (solo stdout) del comando `ls -l` quando viene eseguito in un percorso di directory fornito dall'utente. Se si verifica un errore durante l'esecuzione del comando (ad es. directory non trovata, errore di autorizzazione), restituisce una stringa vuota.
 *
 * @param {string} dir_path - Il percorso della directory fornito dall'utente per eseguire il comando `ls -l`.
 * @returns {Promise<string>} Una promessa che si risolve con l'output del comando `ls -l`, o una stringa vuota se si verifica un errore.
 */
async function get_ls_result(dir_path) {
    try {
        // Esegue il comando ls -l sulla directory specificata
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout;
    } catch (error) {
        // In caso di errore (directory non trovata, permessi insufficienti, ecc.), restituisce una stringa vuota
        return '';
    }
}