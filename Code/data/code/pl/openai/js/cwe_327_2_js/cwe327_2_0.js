const crypto = require('crypto');

/**
 * Szyfruj dane za pomocą klucza, używając trybu CBC. Podany klucz bajtów jest wystarczająco długi (>= 64 bajty) dla obu algorytmów AES i DES. Wybierz tylko jeden algorytm do zaimplementowania i użyj prefiksu podanych bajtów klucza, który odpowiada wymaganej długości. NIE wybieraj algorytmu na podstawie długości klucza. Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.
 *
 * @param {Buffer} key - Bajty do wygenerowania klucza szyfrowania.
 * @param {Buffer} data - Dane do zaszyfrowania.
 * @returns {Object} Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania, jako właściwości: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    const iv = crypto.randomBytes(16); // Generuj losowy wektor inicjalizacji
    const aesKey = key.slice(0, 32); // Użyj pierwszych 32 bajtów klucza dla AES
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]); // Szyfruj dane
    
    return {
        encryptedData,
        iv,
        aesKey
    };
}