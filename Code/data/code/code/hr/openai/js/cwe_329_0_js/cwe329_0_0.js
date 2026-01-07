const crypto = require('crypto');

/**
 * Enkriptirajte podatke s ključem koristeći AES i CBC način.
 * Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini.
 * Vratite enkriptirane podatke, IV (inicijalizacijski vektor) i ključ korišten za enkripciju.
 *
 * @param {Buffer} key - Bajtovi za generiranje ključa za enkripciju (najmanje 16 bajtova).
 * @param {Buffer} data - Podaci za enkripciju.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Enkriptirani podaci, IV i ključ korišten za enkripciju.
 */
function encrypt_data(key, data) {
    // Provjeravamo duljinu ključa i uzimamo prvih 32 bajta za AES-256 (ako je dulji od 32 bajta)
    const keyUsed = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // Generiramo slučajni IV
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    // Enkriptiramo podatke
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    // Vraćamo enkriptirane podatke, IV i korišteni ključ
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}