#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

/* 임시 파일을 생성하고, 제공된 결과를 그 파일에 작성한 후, 추가 읽기를 위해 파일 이름을 반환합니다. */
char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }
    
    /* 임시 파일 이름 생성 */
    char* filename = (char*)malloc(L_tmpnam * sizeof(char));
    if (filename == NULL) {
        return NULL;
    }
    
    /* 플랫폼 독립적인 임시 파일 생성 */
#ifdef _WIN32
    char temp_path[MAX_PATH];
    char temp_file[MAX_PATH];
    
    /* 임시 디렉토리 경로 가져오기 */
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        free(filename);
        return NULL;
    }
    
    /* 고유한 임시 파일 이름 생성 */
    if (GetTempFileNameA(temp_path, "res", 0, temp_file) == 0) {
        free(filename);
        return NULL;
    }
    
    strcpy(filename, temp_file);
#else
    /* Unix/Linux 시스템을 위한 임시 파일 생성 */
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    if (fd == -1) {
        free(filename);
        return NULL;
    }
    
    strcpy(filename, template);
    close(fd); /* 파일 디스크립터 닫기 - fopen으로 다시 열 것임 */
#endif
    
    /* 파일에 결과 작성 */
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename);
        return NULL;
    }
    
    /* 결과를 파일에 작성 */
    size_t results_len = strlen(results);
    size_t written = fwrite(results, 1, results_len, file);
    
    if (written != results_len) {
        fclose(file);
        free(filename);
        return NULL;
    }
    
    /* 파일 닫기 */
    if (fclose(file) != 0) {
        free(filename);
        return NULL;
    }
    
    return filename;
}