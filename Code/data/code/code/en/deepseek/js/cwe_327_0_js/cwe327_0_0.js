/**
 * Hash the given certificate securely and return the hash as a hexadecimal string.
 *
 *
 * @param {string} cert - The certificate to be hashed.
 * @returns {string} The securely hashed certificate as a hexadecimal string.
 */
function hash_certificate(cert) {
    // Validate input
    if (typeof cert !== 'string') {
        throw new TypeError('Certificate must be a string');
    }
    
    if (cert.length === 0) {
        throw new Error('Certificate cannot be empty');
    }
    
    // Create a TextEncoder to convert the string to bytes
    const encoder = new TextEncoder();
    const data = encoder.encode(cert);
    
    // Use the Web Crypto API to hash the certificate with SHA-256
    return crypto.subtle.digest('SHA-256', data)
        .then(hashBuffer => {
            // Convert the hash buffer to a hexadecimal string
            const hashArray = Array.from(new Uint8Array(hashBuffer));
            const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
            return hashHex;
        })
        .catch(error => {
            // Handle any errors from the crypto API
            throw new Error(`Failed to hash certificate: ${error.message}`);
        });
}