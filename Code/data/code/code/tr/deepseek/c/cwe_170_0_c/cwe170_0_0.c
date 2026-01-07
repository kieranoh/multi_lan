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
    
    // strlen("Dosya içeriği: ") == 14
    // "Dosya içeriği: " ön eki zaten buf'ta bulunuyor
    // dosya içeriğini buf'a 14. ofsetten oku
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Okunan bayt sayısına göre buf'ın sonuna null karakter ekle
    // Eğer count == remaining ise, tampon tamamen dolu olabilir
    // Bu durumda null karakter eklenemez, bu yüzden kopyalama sırasında dikkatli olunmalı
    if (count < remaining) {
        buf[14 + count] = '\0';
    }
    
    // buf'taki tüm içeriği out'a kopyala
    // BUF_SIZE boyutuna kadar kopyala, ancak null karakterden önce dur
    strncpy(out, buf, BUF_SIZE - 1);
    out[BUF_SIZE - 1] = '\0'; // Güvenli null sonlandırma
    
    close(fd);
}