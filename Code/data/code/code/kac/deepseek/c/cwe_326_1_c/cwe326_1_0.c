#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    DSA *dsa = NULL;
    BIO *bio = NULL;
    char *key_str = NULL;
    long key_size;
    
    // 1. DSA 매개변수 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // DSA 매개변수 생성 명령 실행 (2048비트 키 길이)
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), "openssl dsaparam -out %s 2048", param_filename);
    char *param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        unlink(param_filename);
        return NULL;
    }
    free(param_result);
    
    // 2. DSA 개인 키 생성
    char key_cmd[256];
    snprintf(key_cmd, sizeof(key_cmd), "openssl gendsa %s", param_filename);
    char *key_result = execute_command(key_cmd);
    if (key_result == NULL) {
        unlink(param_filename);
        return NULL;
    }
    
    // 생성된 키를 BIO에 쓰기
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        free(key_result);
        unlink(param_filename);
        return NULL;
    }
    
    // 키 문자열을 BIO에 쓰기
    BIO_write(bio, key_result, strlen(key_result));
    BIO_seek(bio, 0);
    
    // 3. BIO에서 DSA 키 읽기
    dsa = PEM_read_bio_DSAPrivateKey(bio, NULL, NULL, NULL);
    if (dsa == NULL) {
        BIO_free(bio);
        free(key_result);
        unlink(param_filename);
        return NULL;
    }
    
    // 4. DSA 키를 PEM 형식 문자열로 변환
    BIO *out_bio = BIO_new(BIO_s_mem());
    if (out_bio == NULL) {
        DSA_free(dsa);
        BIO_free(bio);
        free(key_result);
        unlink(param_filename);
        return NULL;
    }
    
    if (!PEM_write_bio_DSAPrivateKey(out_bio, dsa, NULL, NULL, 0, NULL, NULL)) {
        BIO_free(out_bio);
        DSA_free(dsa);
        BIO_free(bio);
        free(key_result);
        unlink(param_filename);
        return NULL;
    }
    
    // 5. 문자열로 변환
    key_size = BIO_get_mem_data(out_bio, &key_str);
    if (key_size <= 0) {
        BIO_free(out_bio);
        DSA_free(dsa);
        BIO_free(bio);
        free(key_result);
        unlink(param_filename);
        return NULL;
    }
    
    // 문자열 복사 (BIO 메모리가 해제되기 전에)
    char *result = malloc(key_size + 1);
    if (result == NULL) {
        BIO_free(out_bio);
        DSA_free(dsa);
        BIO_free(bio);
        free(key_result);
        unlink(param_filename);
        return NULL;
    }
    
    memcpy(result, key_str, key_size);
    result[key_size] = '\0';
    
    // 6. 정리
    BIO_free(out_bio);
    DSA_free(dsa);
    BIO_free(bio);
    free(key_result);
    unlink(param_filename);
    
    return result;
}