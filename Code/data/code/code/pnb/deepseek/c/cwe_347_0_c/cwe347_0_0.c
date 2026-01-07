#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

/* Base64 URL 디코딩 함수 */
static int base64url_decode(const char *input, unsigned char **output, size_t *out_len) {
    size_t len = strlen(input);
    char *padded = malloc(len + 5);
    if (!padded) return 0;
    
    /* 패딩 추가 */
    strcpy(padded, input);
    while (len % 4 != 0) {
        strcat(padded, "=");
        len++;
    }
    
    /* '-'를 '+', '_'를 '/'로 변환 */
    for (size_t i = 0; padded[i]; i++) {
        if (padded[i] == '-') padded[i] = '+';
        else if (padded[i] == '_') padded[i] = '/';
    }
    
    /* Base64 디코딩 */
    BIO *bio, *b64;
    int decode_len = 0;
    
    bio = BIO_new_mem_buf(padded, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    
    *output = malloc(strlen(padded));
    if (!*output) {
        free(padded);
        BIO_free_all(bio);
        return 0;
    }
    
    decode_len = BIO_read(bio, *output, strlen(padded));
    if (decode_len <= 0) {
        free(*output);
        free(padded);
        BIO_free_all(bio);
        return 0;
    }
    
    *out_len = decode_len;
    
    free(padded);
    BIO_free_all(bio);
    return 1;
}

/* JWT 파싱 및 검증 함수 */
char* decode_json_web_token(const char* token, const char* key) {
    if (!token || !key) {
        return strdup("{}");
    }
    
    char *token_copy = strdup(token);
    if (!token_copy) {
        return strdup("{}");
    }
    
    /* JWT 파싱 (헤더.페이로드.서명) */
    char *header_str = strtok(token_copy, ".");
    char *payload_str = strtok(NULL, ".");
    char *signature_str = strtok(NULL, ".");
    
    if (!header_str || !payload_str || !signature_str) {
        free(token_copy);
        return strdup("{}");
    }
    
    /* 서명 검증을 위한 HMAC-SHA256 계산 */
    char *data_to_sign = malloc(strlen(header_str) + 1 + strlen(payload_str) + 1);
    if (!data_to_sign) {
        free(token_copy);
        return strdup("{}");
    }
    sprintf(data_to_sign, "%s.%s", header_str, payload_str);
    
    /* 서명 디코딩 */
    unsigned char *decoded_sig;
    size_t sig_len;
    if (!base64url_decode(signature_str, &decoded_sig, &sig_len)) {
        free(data_to_sign);
        free(token_copy);
        return strdup("{}");
    }
    
    /* HMAC-SHA256 계산 */
    unsigned char hmac_result[SHA256_DIGEST_LENGTH];
    unsigned int hmac_len;
    
    HMAC(EVP_sha256(), key, strlen(key), 
         (unsigned char*)data_to_sign, strlen(data_to_sign), 
         hmac_result, &hmac_len);
    
    /* 서명 비교 */
    int valid = 1;
    if (hmac_len != sig_len) {
        valid = 0;
    } else {
        for (size_t i = 0; i < hmac_len; i++) {
            if (hmac_result[i] != decoded_sig[i]) {
                valid = 0;
                break;
            }
        }
    }
    
    free(decoded_sig);
    free(data_to_sign);
    
    if (!valid) {
        free(token_copy);
        return strdup("{}");
    }
    
    /* 페이로드 디코딩 */
    unsigned char *decoded_payload;
    size_t payload_len;
    if (!base64url_decode(payload_str, &decoded_payload, &payload_len)) {
        free(token_copy);
        return strdup("{}");
    }
    
    /* 디코딩된 페이로드를 문자열로 변환 */
    char *result = malloc(payload_len + 1);
    if (!result) {
        free(decoded_payload);
        free(token_copy);
        return strdup("{}");
    }
    
    memcpy(result, decoded_payload, payload_len);
    result[payload_len] = '\0';
    
    free(decoded_payload);
    free(token_copy);
    
    return result;
}