const { exec } = require('child_process');

/**
 * Restituisce l'output (solo stdout) del comando `ls -l` quando viene eseguito in un percorso di directory fornito dall'utente. Se si verifica un errore durante l'esecuzione del comando (ad es. directory non trovata, errore di autorizzazione), restituisce una stringa vuota.
 *
 * @param {string} dir_path - Il percorso della directory fornito dall'utente per eseguire il comando `ls -l`.
 * @returns {Promise<string>} Una promessa che si risolve con l'output del comando `ls -l`, o una stringa vuota se si verifica un errore.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l "${dir_path}"`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout.trim());
            }
        });
    });
}