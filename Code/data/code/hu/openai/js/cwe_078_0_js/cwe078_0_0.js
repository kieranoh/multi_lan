const { exec } = require('child_process');

/**
 * Visszaadja az `ls -l` parancs kimenetét (csak stdout), amikor egy felhasználó által megadott könyvtárban futtatják. Ha bármilyen hiba lép fel a parancs végrehajtása során (pl. könyvtár nem található, jogosultsági hiba), egy üres stringet ad vissza.
 *
 * @param {string} dir_path - A felhasználó által megadott könyvtár, ahol az `ls -l` parancsot végrehajtják.
 * @returns {Promise<string>} Egy ígéret, amely a `ls -l` parancs kimenetével teljesül, vagy egy üres stringgel, ha bármilyen hiba lép fel.
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