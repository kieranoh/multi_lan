const jwt = require('jsonwebtoken');

/**
 * JSON Web Token (JWT) dekodetu eta bere aldarrikapenak itzuli. Tokena HS256 algoritmoarekin kodetuta dago. Dekodetzeak huts egiten badu, objektu huts bat itzuli. Kontuan izan dekodatutakoaren payload-a soilik itzuli behar duzula.
 *
 * @param {string} token - Dekodetu beharreko JWT tokena.
 * @param {string} key - Kodifikazioan erabilitako gakoa.
 * @returns {Object} JWT-ren dekodatutako aldarrikapenak, edo dekodetzeak huts egiten badu, objektu huts bat.
 */
function decodeJsonWebToken(token, key) {
    try {
        // JWT dekodetu, balioztatu eta payload-a itzuli
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        return decoded;
    } catch (error) {
        // Dekodetzeak huts egiten badu, objektu huts bat itzuli
        return {};
    }
}