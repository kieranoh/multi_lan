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
    // Provjera ulaznih parametara
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('Oba parametra moraju biti Buffer objekti');
    }
    
    if (key.length < 16) {
        throw new Error('Ključ mora imati najmanje 16 bajtova');
    }
    
    // Određivanje duljine ključa za AES-256 (32 bajta)
    const keyLength = 32;
    
    // Koristimo prefiks pruženih bajtova ključa
    const keyUsed = key.slice(0, keyLength);
    
    // Generiranje nasumičnog IV-a (16 bajtova za AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Stvaranje cipher objekta s AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Enkripcija podataka
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // Spajanje svih chunkova u jedan buffer
    const encryptedData = Buffer.concat(encryptedChunks);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}