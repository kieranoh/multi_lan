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
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (err) {
        return {};
    }
}