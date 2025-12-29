const { exec } = require('child_process');

/**
 * Itzuli `ls -l` agindua exekutatzen den erabiltzaileak emandako direktorio bidearen irteera (soilik stdout). Agindua exekutatzean errore bat gertatzen bada (adibidez, direktorioa aurkitu ez, baimen errorea), itzuli string huts bat.
 *
 * @param {string} dir_path - Erabiltzaileak emandako direktorio bidea `ls -l` agindua exekutatzeko.
 * @returns {Promise<string>} `ls -l` aginduaren irteerarekin konprometitutako promesa, edo string huts bat errore bat gertatzen bada.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout, stderr) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout.trim());
            }
        });
    });
}