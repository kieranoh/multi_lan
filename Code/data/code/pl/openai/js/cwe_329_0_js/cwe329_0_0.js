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
    // Upewnij się, że klucz ma odpowiednią długość
    const keyUsed = key.slice(0, 32); // Użyj przynajmniej 256-bitowego klucza
    const iv = crypto.randomBytes(16); // Generowanie losowego wektora inicjalizacji

    // Utworzenie strumienia szyfrowania
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: Buffer.from(encryptedData, 'hex'),
        iv: iv,
        keyUsed: keyUsed
    };
}