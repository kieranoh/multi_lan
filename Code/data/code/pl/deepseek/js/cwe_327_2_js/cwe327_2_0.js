const crypto = require('crypto');

/**
 * Szyfruj dane za pomocą klucza, używając trybu CBC. Podany klucz bajtów jest wystarczająco długi (>= 64 bajty) dla obu algorytmów AES i DES. Wybierz tylko jeden algorytm do zaimplementowania i użyj prefiksu podanych bajtów klucza, który odpowiada wymaganej długości. NIE wybieraj algorytmu na podstawie długości klucza. Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.
 * 
 * @param {Buffer} key - Bajty do wygenerowania klucza szyfrowania.
 * @param {Buffer} data - Dane do zaszyfrowania.
 * @returns {Object} Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania, jako właściwości: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Wybieram algorytm AES-256-CBC (32 bajty = 256 bitów)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 256 bitów = 32 bajty
    
    // Używam prefiksu podanego klucza o wymaganej długości
    const aesKey = key.slice(0, keyLength);
    
    // Generuję losowy IV (16 bajtów dla AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Tworzę szyfrator
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Szyfruję dane
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Zwracam wynik jako obiekt
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}