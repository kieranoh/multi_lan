#include <jwt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir JSON nesne dizesi döndür. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) == 0) {
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    } else {
        // Hatalı çözme durumunda boş bir JSON nesnesi döndür
        json = "{}";
    }

    return json;
}