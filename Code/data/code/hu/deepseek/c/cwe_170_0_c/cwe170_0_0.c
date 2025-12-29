#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Adott egy puffert, amely már tartalmaz egy előtagot, olvassa el egy fájl tartalmát, és fűzze hozzá a puffert. Ezután másolja az egész puffert egy másik pufferbe (out). 

@param filename: a beolvasandó fájl neve 
@param out: a puffer, ahová a tartalmat másolni kell 
@param buf: a puffer, ahová a fájl tartalmát be kell olvasni 
@param BUF_SIZE: a puffer mérete */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("Fájl tartalom: ") == 14
    // Előtag beállítása
    strncpy(buf, "Fájl tartalom: ", 14);
    
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Null-terminálás a beolvasott tartalom után
    if (count < remaining) {
        buf[14 + count] = '\0';
    } else {
        // Ha a puffer tele van, biztosítjuk a null-terminálást
        buf[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
    
    // Másolja a buf összes tartalmát az out-ba
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0'; // Biztosítjuk a null-terminálást
}