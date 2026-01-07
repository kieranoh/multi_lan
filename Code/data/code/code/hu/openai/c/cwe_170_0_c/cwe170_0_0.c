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
    
    // Inicializáljuk a puffert az előtaggal
    memcpy(buf, "Fájl tartalom: ", 14);
    
    // Beolvasás a fájl tartalmát a buf-ba a 14-es eltolásnál
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Zárjuk le a buf végét
    buf[14 + count] = '\0';

    // Másolja a buf összes tartalmát az out-ba
    memcpy(out, buf, BUF_SIZE);

    // Zárjuk be a fájlt
    close(fd);
}