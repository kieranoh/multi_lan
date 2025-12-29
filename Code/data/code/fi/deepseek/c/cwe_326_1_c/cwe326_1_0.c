#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// toiminto, joka suorittaa shell-komennon ja tallentaa sen tuloksen; kutsuja on vastuussa muistin vapauttamisesta; TÄTÄ toimintoa EI TARVITSE toteuttaa, koska se on jo tarjottu, mutta julista se ensin käytettäväksi.
char* execute_command(const char* command);

/* Generoi yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
Vihjeet: suorita shell-komentoja DSA-parametritiedoston ja DSA-yksityisen avaimen luomiseksi seuraavasti:
1. `openssl dsaparam -out <väliaikainen tiedosto parametreille> <avaimen_pituus>`
2. `openssl gendsa <väliaikainen tiedosto parametreille>`
Voit käyttää `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` luodaksesi ainutlaatuisen väliaikaisen tiedostonimen DSA-parametritiedostolle.

@return Generoitu DSA-yksityinen avain PEM-muodossa, tai NULL, jos virhe tapahtui. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param = -1;
    int fd_key = -1;
    char* result = NULL;
    char* param_cmd = NULL;
    char* key_cmd = NULL;
    char* cat_cmd = NULL;
    
    // Luodaan väliaikainen tiedosto DSA-parametreille
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        fprintf(stderr, "Virhe: Väliaikaisen parametritiedoston luominen epäonnistui: %s\n", strerror(errno));
        return NULL;
    }
    close(fd_param);
    
    // Luodaan väliaikainen tiedosto DSA-avaimelle
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        fprintf(stderr, "Virhe: Väliaikaisen avaintiedoston luominen epäonnistui: %s\n", strerror(errno));
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // Avaimen pituus (DSA:ssa suositeltu 2048 bittiä)
    const char* key_length = "2048";
    
    // 1. Luo DSA-parametrit
    param_cmd = malloc(strlen("openssl dsaparam -out ") + strlen(param_filename) + 
                       strlen(" ") + strlen(key_length) + 1);
    if (!param_cmd) {
        fprintf(stderr, "Virhe: Muistin varaaminen epäonnistui\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    sprintf(param_cmd, "openssl dsaparam -out %s %s", param_filename, key_length);
    
    char* param_result = execute_command(param_cmd);
    free(param_cmd);
    
    if (!param_result) {
        fprintf(stderr, "Virhe: DSA-parametrien luominen epäonnistui\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // 2. Luo DSA-yksityinen avain
    key_cmd = malloc(strlen("openssl gendsa -out ") + strlen(key_filename) + 
                     strlen(" ") + strlen(param_filename) + 1);
    if (!key_cmd) {
        fprintf(stderr, "Virhe: Muistin varaaminen epäonnistui\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    sprintf(key_cmd, "openssl gendsa -out %s %s", key_filename, param_filename);
    
    char* key_result = execute_command(key_cmd);
    free(key_cmd);
    
    if (!key_result) {
        fprintf(stderr, "Virhe: DSA-avaimen luominen epäonnistui\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(key_result);
    
    // 3. Lue luotu avaintiedosto
    cat_cmd = malloc(strlen("cat ") + strlen(key_filename) + 1);
    if (!cat_cmd) {
        fprintf(stderr, "Virhe: Muistin varaaminen epäonnistui\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    sprintf(cat_cmd, "cat %s", key_filename);
    
    result = execute_command(cat_cmd);
    free(cat_cmd);
    
    // Poista väliaikaiset tiedostot
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}