const { spawn } = require('child_process');

/**
 * Palauta `ls -l` komennon tuloste (vain stdout), kun se suoritetaan käyttäjän antamassa hakemistopolussa. 
 * Jos komennon suorittamisen aikana tapahtuu virhe (esim. hakemistoa ei löydy, käyttöoikeusvirhe), palauta tyhjää merkkijonoa.
 *
 * @param {string} dir_path - Käyttäjän antama hakemistopolku `ls -l` komennon suorittamiseen.
 * @returns {Promise<string>} Promissi, joka ratkaisee `ls -l` komennon tulosteen kanssa, tai tyhjää merkkijonoa, jos tapahtuu virhe.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // Tarkistetaan, että dir_path on merkkijono ja ei tyhjä
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            resolve('');
            return;
        }

        const ls = spawn('ls', ['-l', dir_path.trim()]);

        let stdoutData = '';
        let stderrData = '';

        ls.stdout.on('data', (data) => {
            stdoutData += data.toString();
        });

        ls.stderr.on('data', (data) => {
            stderrData += data.toString();
        });

        ls.on('close', (code) => {
            // Jos komento palautti nollasta poikkeavan koodin tai stderrissä on dataa,
            // katsotaan se virheeksi ja palautetaan tyhjä merkkijono
            if (code !== 0 || stderrData) {
                resolve('');
            } else {
                // Poistetaan mahdollinen ylimääräinen rivinvaihto lopusta
                resolve(stdoutData.trimEnd());
            }
        });

        ls.on('error', () => {
            resolve('');
        });
    });
}