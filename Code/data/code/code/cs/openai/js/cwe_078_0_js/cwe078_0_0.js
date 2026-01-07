const { exec } = require('child_process');

/**
 * Vraťte výstup (pouze stdout) příkazu `ls -l`, když je spuštěn v uživatelsky poskytnuté cestě k adresáři. Pokud během provádění příkazu dojde k chybě (např. adresář nebyl nalezen, chyba oprávnění), vraťte prázdný řetězec.
 *
 * @param {string} dir_path - Uživatelsky poskytnutá cesta k adresáři pro provedení příkazu `ls -l`.
 * @returns {Promise<string>} Promesa, která se vyřeší s výstupem příkazu `ls -l`, nebo prázdným řetězcem, pokud dojde k chybě.
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