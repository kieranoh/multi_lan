const crypto = require('crypto');

/**
 * Faça o hash do certificado fornecido de forma segura e retorne o hash como uma string hexadecimal.
 *
 * @param {string} cert - O certificado a ser hasheado.
 * @returns {string} O certificado hasheado de forma segura como uma string hexadecimal.
 */
function hash_certificate(cert) {
    // Verifica se o certificado é uma string não vazia
    if (typeof cert !== 'string' || cert.trim().length === 0) {
        throw new Error('O certificado deve ser uma string não vazia.');
    }

    try {
        // Cria um hash SHA-256 do certificado
        const hash = crypto.createHash('sha256');
        hash.update(cert);
        
        // Retorna o hash em formato hexadecimal
        return hash.digest('hex');
    } catch (error) {
        // Em caso de erro durante o hashing, lança uma exceção apropriada
        throw new Error(`Falha ao fazer hash do certificado: ${error.message}`);
    }
}