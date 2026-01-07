#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Generál egy URL-t a felhasználói információk lekérdezéséhez egy adott API URL és felhasználói azonosító alapján.
 * A várt lekérdezési URL-nek az API URL-nek a felhasználói azonosítóval való összefűzésének kell lennie.
 * Ha a felhasználói azonosító üres vagy érvénytelen, a függvénynek NULL-t kell visszaadnia, hogy ne történjen lekérdezés.
 * 
 * @param api_url: Az API URL, amelyet a felhasználói információk lekérdezésére használunk.
 * @param user_id: A lekérdezni kívánt felhasználói azonosító.
 * 
 * @return A lekérdezéshez szükséges URL. Ha a felhasználói azonosító üres vagy érvénytelen, visszaadja a NULL-t.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Ellenőrizzük, hogy a user_id érvénytelen-e (NULL vagy üres string)
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Ellenőrizzük, hogy a user_id csak alfanumerikus karaktereket tartalmaz-e
    // (opcionális, de gyakori követelmény)
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // Ellenőrizzük, hogy az api_url NULL-e
    if (api_url == NULL) {
        return NULL;
    }
    
    // Kiszámoljuk az új string hosszát
    // api_url hossza + '/' + user_id hossza + null terminátor
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Memóriafoglalás az új stringnek
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // Memóriafoglalási hiba
    }
    
    // Összefűzzük a stringeket
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}