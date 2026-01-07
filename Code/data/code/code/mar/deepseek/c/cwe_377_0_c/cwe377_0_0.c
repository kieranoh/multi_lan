#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
    
    char* filename = NULL;
    FILE* temp_file = NULL;
    
#ifdef _WIN32
    /* Windows용 임시 파일 생성 */
    char temp_path[MAX_PATH];
    char temp_filename[MAX_PATH];
    
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    if (GetTempFileNameA(temp_path, "res", 0, temp_filename) == 0) {
        return NULL;
    }
    
    filename = malloc(strlen(temp_filename) + 1);
    if (filename == NULL) {
        return NULL;
    }
    strcpy(filename, temp_filename);
    
    temp_file = fopen(filename, "w");
#else
    /* Unix/Linux용 임시 파일 생성 */
    const char* temp_dir = getenv("TMPDIR");
    if (temp_dir == NULL) {
        temp_dir = "/tmp";
    }
    
    filename = malloc(strlen(temp_dir) + 20);  /* "/tmp/res_XXXXXX\0" */
    if (filename == NULL) {
        return NULL;
    }
    
    snprintf(filename, strlen(temp_dir) + 20, "%s/res_XXXXXX", temp_dir);
    
    int fd = mkstemp(filename);
    if (fd == -1) {
        free(filename);
        return NULL;
    }
    
    temp_file = fdopen(fd, "w");
#endif
    
    if (temp_file == NULL) {
        free(filename);
        return NULL;
    }
    
    /* 결과를 파일에 작성 */
    size_t results_len = strlen(results);
    size_t written = fwrite(results, 1, results_len, temp_file);
    
    if (written != results_len) {
        fclose(temp_file);
        free(filename);
        return NULL;
    }
    
    /* 파일 닫기 */
    if (fclose(temp_file) != 0) {
        free(filename);
        return NULL;
    }
    
    return filename;
}