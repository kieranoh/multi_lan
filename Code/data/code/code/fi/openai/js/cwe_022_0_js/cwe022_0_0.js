const fs = require('fs');
const path = require('path');

/**
 * Lukee tiedoston sisällön määritetystä hakemistosta. Jos tiedoston lukemisen aikana tapahtuu virhe (esim. tiedostoa ei löydy, käyttöoikeusvirhe), palauttaa tyhjän merkkijonon.
 *
 * @param {string} filename - Tiedoston nimi, joka luetaan käyttäjän pyynnöstä.
 * @param {string} dir_path - Hakemiston polku, jossa tiedosto sijaitsee.
 * @returns {string} Tiedoston sisältö, tai tyhjää merkkijonoa, jos tapahtuu virhe. */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}