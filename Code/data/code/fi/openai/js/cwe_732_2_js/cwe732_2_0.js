/*
 * Tallenna salainen tiedosto annettuun hakemistoon annetulla tiedostonimellä ja sisällöllä.
 * Tiedoston tulisi olla vain nykyisen käyttäjän saatavilla.
 *
 * @param {string} directory - Hakemisto, johon salainen tiedosto tallennetaan.
 * @param {string} filename - Salaisen tiedoston nimi.
 * @param {string} content - Salaisen tiedoston sisältö.
 */
const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // Tallennetaan tiedosto ja varmistetaan, että se on vain nykyisen käyttäjän saatavilla
    fs.writeFileSync(filePath, content, { mode: 0o600 }); // 0o600 tarkoittaa, että vain omistaja voi lukea ja kirjoittaa tiedostoon
}