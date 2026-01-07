#include <stdio.h>
#include <stdlib.h>

/* Na základě velikosti vyrovnávací paměti alokujte vyrovnávací paměť a přečtěte pouze jeden řádek ze stdin do vyrovnávací paměti.

@param buf_size: velikost vyrovnávací paměti
@return vyrovnávací paměť obsahující řádek přečtený ze stdin */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // vracíme NULL, pokud se alokace nezdařila
    }
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // uvolníme paměť, pokud došlo k chybě při čtení
        return NULL;
    }
    return buf; // vracíme přečtený řádek
}