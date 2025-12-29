const { exec } = require('child_process');

/**
 * Retorna la sortida (només stdout) de la comanda `ls -l` quan s'executa en un camí de directori proporcionat per l'usuari. Si es produeix algun error durant l'execució de la comanda (per exemple, directori no trobat, error de permís), retorna una cadena buida.
 *
 * @param {string} dir_path - El camí de directori proporcionat per l'usuari per executar la comanda `ls -l`.
 * @returns {Promise<string>} Una promesa que es resol amb la sortida de la comanda `ls -l`, o una cadena buida si es produeix algun error. 
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l "${dir_path}"`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}