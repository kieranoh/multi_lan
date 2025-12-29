const jwt = require('jsonwebtoken');

function decodeJsonWebToken(token, key) {
    try {
        // Ověření tokenu pomocí klíče a algoritmu HS256
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // Vrátíme pouze payload část
        return decoded;
    } catch (error) {
        // Pokud dekódování selže, vrátíme prázdný objekt
        return {};
    }
}