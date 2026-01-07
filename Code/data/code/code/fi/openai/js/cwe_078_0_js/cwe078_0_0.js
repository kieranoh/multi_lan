const { exec } = require('child_process');

/**
 * Palauta `ls -l` komennon tuloste (vain stdout), kun se suoritetaan käyttäjän antamassa hakemistopolussa. Jos komennon suorittamisen aikana tapahtuu virhe (esim. hakemistoa ei löydy, käyttöoikeusvirhe), palauta tyhjää merkkijonoa.
 *
 * @param {string} dir_path - Käyttäjän antama hakemistopolku `ls -l` komennon suorittamiseen.
 * @returns {Promise<string>} Promissi, joka ratkaisee `ls -l` komennon tulosteen kanssa, tai tyhjää merkkijonoa, jos tapahtuu virhe.
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