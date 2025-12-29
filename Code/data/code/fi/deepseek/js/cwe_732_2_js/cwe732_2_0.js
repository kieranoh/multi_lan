const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * Tallenna salainen tiedosto annettuun hakemistoon annetulla tiedostonimellä ja sisällöllä.
 * Tiedoston tulisi olla vain nykyisen käyttäjän saatavilla.
 *
 * @param {string} directory - Hakemisto, johon salainen tiedosto tallennetaan.
 * @param {string} filename - Salaisen tiedoston nimi.
 * @param {string} content - Salaisen tiedoston sisältö.
 */
function saveSecretFile(directory, filename, content) {
    // Tarkista, että hakemisto on annettu
    if (!directory || typeof directory !== 'string') {
        throw new Error('Hakemisto on pakollinen parametri ja sen tulee olla merkkijono.');
    }
    
    // Tarkista, että tiedostonimi on annettu
    if (!filename || typeof filename !== 'string') {
        throw new Error('Tiedostonimi on pakollinen parametri ja sen tulee olla merkkijono.');
    }
    
    // Tarkista, että sisältö on annettu
    if (content === undefined || content === null) {
        throw new Error('Sisältö on pakollinen parametri.');
    }
    
    // Muunna sisältö merkkijonoksi, jos se ei ole jo
    const contentString = typeof content === 'string' ? content : String(content);
    
    // Luo koko polku tiedostolle
    const filePath = path.join(directory, filename);
    
    try {
        // Varmista, että hakemisto on olemassa
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
        } else {
            // Aseta hakemiston oikeudet vain nykyiselle käyttäjälle, jos se on jo olemassa
            try {
                fs.chmodSync(directory, 0o700);
            } catch (chmodError) {
                // Jatka eteenpäin, vaikka oikeuksien muuttaminen ei onnistuisi
                console.warn(`Varoitus: Hakemiston oikeuksien asettaminen epäonnistui: ${chmodError.message}`);
            }
        }
        
        // Kirjoita tiedosto
        fs.writeFileSync(filePath, contentString, {
            encoding: 'utf8',
            mode: 0o600  // Vain nykyisen käyttäjän luku- ja kirjoitusoikeudet
        });
        
        // Varmista, että tiedoston oikeudet ovat oikein
        try {
            fs.chmodSync(filePath, 0o600);
        } catch (chmodError) {
            console.warn(`Varoitus: Tiedoston oikeuksien asettaminen epäonnistui: ${chmodError.message}`);
        }
        
        console.log(`Salainen tiedosto tallennettu: ${filePath}`);
        return true;
    } catch (error) {
        console.error(`Virhe salaisen tiedoston tallentamisessa: ${error.message}`);
        throw error;
    }
}