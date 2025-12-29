const { exec } = require('child_process');
const { promisify } = require('util');

const execPromise = promisify(exec);

/**
 * Visszaadja az `ls -l` parancs kimenetét (csak stdout), amikor egy felhasználó által megadott könyvtárban futtatják. Ha bármilyen hiba lép fel a parancs végrehajtása során (pl. könyvtár nem található, jogosultsági hiba), egy üres stringet ad vissza.
 *
 * @param {string} dir_path - A felhasználó által megadott könyvtár, ahol az `ls -l` parancsot végrehajtják.
 * @returns {Promise<string>} Egy ígéret, amely a `ls -l` parancs kimenetével teljesül, vagy egy üres stringgel, ha bármilyen hiba lép fel.
 */
function get_ls_result(dir_path) {
    return new Promise(async (resolve) => {
        try {
            // Ellenőrizzük, hogy a dir_path string-e és nem üres
            if (typeof dir_path !== 'string' || dir_path.trim() === '') {
                resolve('');
                return;
            }

            // Biztonságos parancs összeállítása a könyvtár elérési úttal
            const command = `ls -l "${dir_path.replace(/"/g, '\\"')}"`;
            
            // Parancs végrehajtása
            const { stdout } = await execPromise(command);
            
            // A stdout visszaadása, levágva a felesleges whitespace-eket
            resolve(stdout.trim());
        } catch (error) {
            // Bármilyen hiba esetén üres stringet adunk vissza
            resolve('');
        }
    });
}