const { exec } = require('child_process');

/**
 * Vraća izlaz (samo stdout) `ls -l` naredbe kada se izvrši u korisnički zadanom putu do direktorija. Ako dođe do bilo kakve pogreške tijekom izvršenja naredbe (npr. direktorij nije pronađen, pogreška s dozvolama), vraća prazni niz.
 *
 * @param {string} dir_path - Korisnički zadan put do direktorija za izvršenje `ls -l` naredbe.
 * @returns {Promise<string>} Promesa koja se rješava s izlazom `ls -l` naredbe, ili praznim nizom ako dođe do bilo kakve pogreške. 
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}