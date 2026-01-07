const fs = require('fs');
const path = require('path');

/**
 * Lukee tiedoston sisällön määritetystä hakemistosta. Jos tiedoston lukemisen aikana tapahtuu virhe (esim. tiedostoa ei löydy, käyttöoikeusvirhe), palauttaa tyhjän merkkijonon.
 *
 * @param {string} filename - Tiedoston nimi, joka luetaan käyttäjän pyynnöstä.
 * @param {string} dir_path - Hakemiston polku, jossa tiedosto sijaitsee.
 * @returns {string} Tiedoston sisältö, tai tyhjää merkkijonoa, jos tapahtuu virhe.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // Muodosta täydellinen polku tiedostoon
        const filePath = path.join(dir_path, filename);
        
        // Tarkista, että polku on turvallinen (ei sisällä '..' tai absoluuttisia polkuja, jotka voivat johtaa hakemiston ulkopuolelle)
        const resolvedPath = path.resolve(dir_path, filename);
        if (!resolvedPath.startsWith(path.resolve(dir_path))) {
            return '';
        }
        
        // Lue tiedosto synkronisesti (käyttää UTF-8 -merkistöä oletuksena)
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // Kaikki virheet: tiedostoa ei löydy, käyttöoikeusvirheet, yms.
        return '';
    }
}