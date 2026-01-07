const { exec } = require('child_process');

/**
 * Vraća izlaz (samo stdout) komande `ls -l` kada se izvrši u korisnički obezbeđenoj putanji direktorijuma. Ako dođe do bilo kakve greške tokom izvršenja komande (npr. direktorijum nije pronađen, greška u dozvolama), vraća prazan string.
 *
 * @param {string} dir_path - Korisnički obezbeđena putanja direktorijuma za izvršenje komande `ls -l`.
 * @returns {Promise<string>} Promisa koja se rešava sa izlazom komande `ls -l`, ili praznim stringom ako dođe do bilo kakve greške. */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l "${dir_path}"`, (error, stdout, stderr) => {
            if (error) {
                // Ako dođe do greške, vraćamo prazan string
                resolve('');
            } else {
                // Vraćamo izlaz komande
                resolve(stdout);
            }
        });
    });
}