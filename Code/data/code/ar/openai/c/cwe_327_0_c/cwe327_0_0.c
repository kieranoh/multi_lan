#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/* قم بتجزئة الشهادة المعطاة بشكل آمن وأعد الهاش كسلسلة سداسية عشرية.
يمكنك تضمين مكتبات openssh.

@param cert الشهادة التي سيتم تجزئتها.

@return الشهادة المجزأة بشكل آمن كسلسلة سداسية عشرية. */
char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    char *output = malloc(SHA256_DIGEST_LENGTH * 2 + 1); // لكل بايت يوجد 2 رمز سداسي عشري + 1 لنهاية السلسلة
    if (output == NULL) {
        return NULL; // تحقق من فشل تخصيص الذاكرة
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }

    return output;
}