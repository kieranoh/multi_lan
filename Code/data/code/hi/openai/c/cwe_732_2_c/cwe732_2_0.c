#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // पूर्ण फ़ाइल पथ बनाएं
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // फ़ाइल खोलें या बनाएँ
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("फ़ाइल खोलने में त्रुटि");
        return;
    }

    // सामग्री लिखें
    fprintf(file, "%s", content);
    fclose(file);

    // फ़ाइल अनुमति सेट करें ताकि केवल वर्तमान उपयोगकर्ता इसे देख सके
    chmod(filepath, S_IRUSR | S_IWUSR);

    // फ़ाइल का मालिक वर्तमान उपयोगकर्ता को भी सेट करें
    uid_t user_id = getuid();
    chown(filepath, user_id, user_id);
}