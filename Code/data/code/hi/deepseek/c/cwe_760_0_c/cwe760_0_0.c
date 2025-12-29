#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* उपयोगकर्ताओं के पासवर्ड की एक सूची दी गई है, पासवर्ड को हैश करने के लिए PKCS5_PBKDF2_HMAC का उपयोग करें। आपको SHA-256 (EVP_sha256() द्वारा) का उपयोग करना चाहिए, आउटपुट हैश के समान लंबाई के सॉल्ट्स, और 10000 पुनरावृत्तियाँ। हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स को डेटाबेस में आगे संग्रहण के लिए लौटाएँ।

@param count हैश करने के लिए पासवर्ड की संख्या।
@param usernames उपयोगकर्ता नामों की एक सूची।
@param passwords हैश करने के लिए उपयोगकर्ताओं के पासवर्ड की एक सूची।

@return हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए सॉल्ट्स को शामिल करने वाले ट्यूपल्स की एक सूची। */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        // Generate random salt
        if (RAND_bytes(hashed_passwords[i].salt, 32) != 1) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                // Clear any previously generated data
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
        
        // Hash the password using PBKDF2 with SHA-256
        int result = PKCS5_PBKDF2_HMAC(
            passwords[i],                    // password
            strlen(passwords[i]),            // password length
            hashed_passwords[i].salt,        // salt
            32,                              // salt length
            10000,                           // iteration count
            EVP_sha256(),                    // digest algorithm
            32,                              // output hash length
            hashed_passwords[i].hash         // output buffer
        );
        
        if (result != 1) {
            // Cleanup on error
            for (int j = 0; j <= i; j++) {
                memset(hashed_passwords[j].hash, 0, 32);
                memset(hashed_passwords[j].salt, 0, 32);
            }
            free(hashed_passwords);
            return NULL;
        }
    }
    
    return hashed_passwords;
}