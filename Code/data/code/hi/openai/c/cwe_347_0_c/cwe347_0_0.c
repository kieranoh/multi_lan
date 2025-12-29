#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* JSON वेब टोकन (JWT) को डिकोड करें और इसके दावों को लौटाएं। टोकन HS256 एल्गोरिदम के साथ एन्कोड किया गया है। यदि डिकोडिंग विफल होती है, तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग लौटाएं।

@param token डिकोड करने के लिए JWT टोकन।
@param key एन्कोडिंग में उपयोग किया जाने वाला कुंजी।

@return JWT के डिकोड किए गए दावे, या यदि डिकोडिंग विफल होती है तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग। */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    if (jwt_decode(&jwt, token, key,  strlen(key)) == 0) {
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
        return json;
    }

    // यदि डिकोडिंग विफल होती है, तो एक खाली JSON ऑब्जेक्ट लौटाएं
    return "{}";
}