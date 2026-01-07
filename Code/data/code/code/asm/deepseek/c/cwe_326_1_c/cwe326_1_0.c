#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// 쉘 명령을 실행하고 그 출력을 캡처하는 함수; 호출자가 메모리를 해제할 책임이 있습니다
char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고, PEM 형식으로 내보내어 문자열로 반환합니다.
힌트: 다음과 같이 쉘 명령을 실행하여 DSA 파라미터 파일과 DSA 개인 키를 생성하세요:
1. `openssl dsaparam -out <파라미터를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <파라미터를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 파라미터 파일에 대한 고유한 임시 파일 이름을 생성할 수 있습니다.

@return 생성된 DSA 개인 키를 PEM 형식으로 반환하거나, 오류가 발생한 경우 NULL을 반환합니다. */
char* create_dsa_key() {
    const int key_length = 1024;
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_command[512];
    char* dsa_key_pem = NULL;
    FILE* fp = NULL;
    DSA* dsa = NULL;
    BIO* bio = NULL;
    BUF_MEM* buf_mem = NULL;
    
    // 임시 파라미터 파일 생성
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // DSA 파라미터 생성 명령 실행
    snprintf(key_command, sizeof(key_command), 
             "openssl dsaparam -out %s %d", param_filename, key_length);
    char* param_output = execute_command(key_command);
    free(param_output); // 출력은 필요하지 않음
    
    if (param_output == NULL) {
        // 명령 실행 실패
        unlink(param_filename);
        return NULL;
    }
    
    // DSA 개인 키 생성 명령 실행
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa %s", param_filename);
    char* key_output = execute_command(key_command);
    
    // 임시 파라미터 파일 삭제
    unlink(param_filename);
    
    if (key_output == NULL) {
        return NULL;
    }
    
    // OpenSSL BIO를 사용하여 PEM 형식의 키를 메모리에 저장
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        free(key_output);
        return NULL;
    }
    
    // 문자열에서 DSA 키 파싱
    BIO_puts(bio, key_output);
    free(key_output);
    
    dsa = PEM_read_bio_DSAPrivateKey(bio, NULL, NULL, NULL);
    if (dsa == NULL) {
        BIO_free(bio);
        return NULL;
    }
    
    // DSA 키를 PEM 형식으로 메모리에 쓰기
    BIO* out_bio = BIO_new(BIO_s_mem());
    if (out_bio == NULL) {
        DSA_free(dsa);
        BIO_free(bio);
        return NULL;
    }
    
    if (!PEM_write_bio_DSAPrivateKey(out_bio, dsa, NULL, NULL, 0, NULL, NULL)) {
        DSA_free(dsa);
        BIO_free(bio);
        BIO_free(out_bio);
        return NULL;
    }
    
    // 메모리에서 PEM 문자열 가져오기
    BIO_get_mem_ptr(out_bio, &buf_mem);
    if (buf_mem == NULL || buf_mem->length == 0) {
        DSA_free(dsa);
        BIO_free(bio);
        BIO_free(out_bio);
        return NULL;
    }
    
    dsa_key_pem = (char*)malloc(buf_mem->length + 1);
    if (dsa_key_pem == NULL) {
        DSA_free(dsa);
        BIO_free(bio);
        BIO_free(out_bio);
        return NULL;
    }
    
    memcpy(dsa_key_pem, buf_mem->data, buf_mem->length);
    dsa_key_pem[buf_mem->length] = '\0';
    
    // 리소스 정리
    DSA_free(dsa);
    BIO_free(bio);
    BIO_free(out_bio);
    
    return dsa_key_pem;
}