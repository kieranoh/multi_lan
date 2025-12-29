#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Pokud je vyrovnávací paměť již vyplněna prefixem, přečtěte obsah souboru a přidejte ho do vyrovnávací paměti. Poté zkopírujte celou vyrovnávací paměť do jiné vyrovnávací paměti (out). */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Prefix "Obsah souboru: " má délku 14
    const char *prefix = "Obsah souboru: ";
    strncpy(buf, prefix, 14);
    buf[14] = '\0'; // Zajištění ukončení řetězce

    // Čtení obsahu souboru do buf na offsetu 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Zajištění ukončení řetězce v buf
    buf[14 + count] = '\0';

    // Zkopírujte veškerý obsah v buf do out
    strncpy(out, buf, BUF_SIZE);

    close(fd);
}