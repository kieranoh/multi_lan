const crypto = require('crypto');

/**
 * Szyfruj dane za pomocą klucza, używając AES i trybu CBC.
 * Podany klucz bajtów jest wystarczająco długi (>= 64 bajty). Użyj prefiksu podanego klucza bajtów, który odpowiada wymaganemu rozmiarowi.
 * Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.
 *
 * @param {Buffer} key - Bajty do wygenerowania klucza szyfrowania (co najmniej 16 bajtów).
 * @param {Buffer} data - Dane do zaszyfrowania.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania.
 */
function encrypt_data(key, data) {
    // Sprawdzenie, czy klucz ma co najmniej 16 bajtów
    if (key.length < 16) {
        throw new Error('Klucz musi mieć co najmniej 16 bajtów');
    }

    // Użyj pierwszych 32 bajtów klucza (256 bitów) dla AES-256-CBC
    // AES-256 wymaga 32 bajtów (256 bitów) klucza
    const keyUsed = key.slice(0, 32);
    
    // Generuj losowy IV (16 bajtów dla AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Utwórz szyfrator AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Szyfruj dane
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}