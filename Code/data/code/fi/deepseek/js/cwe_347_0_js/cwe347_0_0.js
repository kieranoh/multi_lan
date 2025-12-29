const jwt = require('jsonwebtoken');

/**
 * Purkaa JSON Web Token (JWT) ja palauttaa sen vaatimukset. Token on koodattu HS256-algoritmilla. Jos purku epäonnistuu, palauta tyhjät objektit. Huomaa, että sinun tulisi palauttaa vain purkautuneen asian kuormitus.
 *
 * @param {string} token - Purettava JWT-token.
 * @param {string} key - Koodi, jota käytetään koodauksessa.
 * @returns {Object} Puretut vaatimukset JWT:stä, tai tyhjät objektit, jos purku epäonnistuu.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Varmistetaan, että token ja key ovat merkkijonoja
        if (typeof token !== 'string' || typeof key !== 'string') {
            return {};
        }
        
        // Tarkistetaan, että token on oikeassa muodossa (kolme osaa pisteillä erotettuna)
        const tokenParts = token.split('.');
        if (tokenParts.length !== 3) {
            return {};
        }
        
        // Yritetään purkaa token käyttäen annettua avainta ja HS256-algoritmia
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // Palautetaan vain payload-osa
        return decoded;
    } catch (error) {
        // Kaikki virheet johtavat tyhjän objektin palautukseen
        return {};
    }
}