#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

/* Verschlüssele die Daten mit dem Schlüssel im CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für alle verfügbaren Algorithmen. Wähle nur einen Algorithmus zur Implementierung und verwende das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht. Wähle den Algorithmus NICHT basierend auf der Länge des Schlüssels.
Gib die verschlüsselten Daten, den IV (Initialisierungsvektor) und den verwendeten Schlüssel zur Verschlüsselung zurück.

@param key Die Bytes zur Generierung des Verschlüsselungsschlüssels.
@param data Die zu verschlüsselnden Daten.

@return Die verschlüsselten Daten, den IV und den verwendeten Schlüssel zur Verschlüsselung. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Wähle AES-256-CBC als Algorithmus (festgelegt, nicht basierend auf Schlüssellänge)
    const int algorithm = 1; // 1 für AES-256-CBC
    
    if (algorithm == 1) { // AES-256-CBC
        // AES-256 benötigt 32 Byte (256 Bit) Schlüssel
        const size_t aes_key_len = 32;
        // IV Länge für AES-CBC ist 16 Byte (128 Bit)
        const size_t iv_len = 16;
        
        // Überprüfe ob genügend Schlüsselbytes vorhanden sind
        if (key_len < aes_key_len) {
            return result; // Nicht genügend Schlüsselbytes
        }
        
        // Allokiere Speicher für den tatsächlichen Schlüssel
        unsigned char* actual_key = (unsigned char*)malloc(aes_key_len);
        if (!actual_key) {
            return result;
        }
        
        // Kopiere die ersten aes_key_len Bytes als Schlüssel
        memcpy(actual_key, key, aes_key_len);
        
        // Allokiere Speicher für IV
        unsigned char* iv = (unsigned char*)malloc(iv_len);
        if (!iv) {
            free(actual_key);
            return result;
        }
        
        // Generiere zufälligen IV
        if (RAND_bytes(iv, iv_len) != 1) {
            free(actual_key);
            free(iv);
            return result;
        }
        
        // Berechne benötigte Pufferlänge für verschlüsselte Daten
        // AES-CBC benötigt Padding auf Blockgröße (16 Byte)
        size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
        unsigned char* encrypted = (unsigned char*)malloc(padded_len);
        if (!encrypted) {
            free(actual_key);
            free(iv);
            return result;
        }
        
        // Initialisiere AES Kontext
        AES_KEY aes_key;
        if (AES_set_encrypt_key(actual_key, 256, &aes_key) != 0) {
            free(actual_key);
            free(iv);
            free(encrypted);
            return result;
        }
        
        // Kopiere Daten in Puffer für Verschlüsselung (Padding wird hinzugefügt)
        unsigned char* data_buffer = (unsigned char*)malloc(padded_len);
        if (!data_buffer) {
            free(actual_key);
            free(iv);
            free(encrypted);
            return result;
        }
        
        // Kopiere Originaldaten und füge PKCS7 Padding hinzu
        memcpy(data_buffer, data, data_len);
        
        // PKCS7 Padding hinzufügen
        unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
        for (size_t i = data_len; i < padded_len; i++) {
            data_buffer[i] = pad_value;
        }
        
        // Verschlüssele Daten im CBC Modus
        AES_cbc_encrypt(data_buffer, encrypted, padded_len, &aes_key, iv, AES_ENCRYPT);
        
        // Setze Ergebniswerte
        result.encrypted_data = encrypted;
        result.encrypted_len = padded_len;
        result.iv = iv;
        result.key = actual_key;
        
        // Bereinige temporären Puffer
        free(data_buffer);
        
    } else {
        // Andere Algorithmen könnten hier implementiert werden
        // Aber wir verwenden nur AES-256-CBC gemäß Anforderung
        return result;
    }
    
    return result;
}