/**
 * 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
 *
 * @param {string} cert - 해시할 인증서입니다.
 * @returns {string} 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
 */
function hash_certificate(cert) {
    // Create a new instance of the SubtleCrypto interface
    const encoder = new TextEncoder();
    const data = encoder.encode(cert);

    // Use the digest method to create a SHA-256 hash
    return crypto.subtle.digest('SHA-256', data).then(hashBuffer => {
        // Convert the hash buffer to a hex string
        const hashArray = Array.from(new Uint8Array(hashBuffer)); // Convert buffer to byte array
        const hashHex = hashArray.map(b => ('00' + b.toString(16)).slice(-2)).join(''); // Convert bytes to hex
        return hashHex; // Return the hex string
    });
}