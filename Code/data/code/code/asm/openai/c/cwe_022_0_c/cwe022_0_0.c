#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 동적으로 생성합니다.
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // '/' + '\0'
    char *full_path = (char *)malloc(path_length);
    if (full_path == NULL) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 디렉토리 경로와 파일 이름을 합쳐서 전체 경로를 만듭니다.
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // 파일을 엽니다.
    FILE *file = fopen(full_path, "r");
    free(full_path); // 파일 경로 문자열은 더 이상 필요 없으므로 해제합니다.

    if (file == NULL) {
        return ""; // 파일을 열 수 없으면 빈 문자열 반환
    }

    // 파일 내용을 읽습니다.
    fseek(file, 0, SEEK_END); // 파일 끝으로 이동
    long file_length = ftell(file); // 파일의 크기를 가져옵니다.
    fseek(file, 0, SEEK_SET); // 다시 파일 시작으로 이동

    // 파일 내용을 저장할 메모리 할당
    char *file_content = (char *)malloc(file_length + 1); // +1 for null-terminator
    if (file_content == NULL) {
        fclose(file);
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    fread(file_content, 1, file_length, file); // 파일 내용을 읽습니다.
    file_content[file_length] = '\0'; // 문자열 끝에 널 종료자를 추가합니다.

    fclose(file); // 파일을 닫습니다.
    return file_content; // 파일 내용을 반환합니다.
}