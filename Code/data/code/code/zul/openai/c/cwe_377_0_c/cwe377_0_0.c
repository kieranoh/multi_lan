#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 임시 파일을 생성하고, 제공된 결과를 그 파일에 작성한 후, 추가 읽기를 위해 파일 이름을 반환합니다. */
char* write_results(const char* results) {
    // Create a temporary file
    char* filename = tempnam(NULL, "tmpfile_");
    if (filename == NULL) {
        return NULL; // Return NULL if tempnam fails
    }

    // Open the temporary file for writing
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename);
        return NULL; // Return NULL if fopen fails
    }

    // Write the results to the file
    fprintf(file, "%s", results);
    
    // Close the file
    fclose(file);

    // Return the filename for further reading
    return filename;
}