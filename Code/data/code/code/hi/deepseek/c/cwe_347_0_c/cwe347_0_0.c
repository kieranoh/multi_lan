#include <jwt.h>
#include <string.h>
#include <stdlib.h>

/* JSON वेब टोकन (JWT) को डिकोड करें और इसके दावों को लौटाएं। टोकन HS256 एल्गोरिदम के साथ एन्कोड किया गया है। यदि डिकोडिंग विफल होती है, तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग लौटाएं।

@param token डिकोड करने के लिए JWT टोकन।
@param key एन्कोडिंग में उपयोग किया जाने वाला कुंजी।

@return JWT के डिकोड किए गए दावे, या यदि डिकोडिंग विफल होती है तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग। */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // JWT पार्स करने का प्रयास करें
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // डिकोडिंग विफल - खाली JSON ऑब्जेक्ट लौटाएं
        result = strdup("{}");
        return result;
    }
    
    // JWT से दावों को JSON स्ट्रिंग के रूप में प्राप्त करें
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims != NULL) {
        // JSON स्ट्रिंग की प्रतिलिपि बनाएं
        result = strdup(json_claims);
    } else {
        // यदि कोई दावे नहीं हैं, तो खाली JSON ऑब्जेक्ट लौटाएं
        result = strdup("{}");
    }
    
    // JWT ऑब्जेक्ट को मुक्त करें
    jwt_free(jwt);
    
    return result;
}