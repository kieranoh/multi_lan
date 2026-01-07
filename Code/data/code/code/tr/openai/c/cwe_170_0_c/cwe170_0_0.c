#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Önceden bir ön ek ile doldurulmuş bir tampon verildiğinde, bir dosyanın içeriğini okuyun ve tamponun sonuna ekleyin. Ardından, tüm tamponu başka bir tampona (out) kopyalayın.

@param filename: okunacak dosyanın adı
@param out: içeriğin kopyalanacağı tampon
@param buf: dosya içeriğinin okunacağı tampon
@param BUF_SIZE: tamponun boyutu */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // "Dosya içeriği: " ön ekini buf'a kopyala
    strcpy(buf, "Dosya içeriği: ");
    
    // Dosya içeriğini buf'a 14. ofsetten oku
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // buf'taki tüm içeriği out'a kopyala
    strcpy(out, buf);
    
    close(fd);
}