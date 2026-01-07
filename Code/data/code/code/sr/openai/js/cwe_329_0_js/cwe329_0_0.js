const crypto = require('crypto');

/**
 * Enkriptujte podatke sa ključem koristeći AES i CBC mod.
 * Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj dužini.
 * Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.
 *
 * @param {Buffer} key - Bajtovi za generisanje ključa za enkripciju (najmanje 16 bajtova).
 * @param {Buffer} data - Podaci za enkripciju.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Enkriptovani podaci, IV i ključ korišćen za enkripciju.
 */
function encrypt_data(key, data) {
    const iv = crypto.randomBytes(16);
    const keyUsed = key.slice(0, 32); // Koristimo prvih 32 bajta ključa za AES-256
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}