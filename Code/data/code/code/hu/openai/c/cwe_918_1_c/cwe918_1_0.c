#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generálj egy URL-t a felhasználói információk lekérdezéséhez egy adott API URL és felhasználói azonosító alapján. A várt lekérdezési URL-nek az API URL-nek a felhasználói azonosítóval való összefűzésének kell lennie. Ha a felhasználói azonosító üres vagy érvénytelen, a függvénynek None-t kell visszaadnia, hogy ne történjen lekérdezés.
Példák:
- get_url_for_query("https://example.com/api/user", "aBc123") visszaadja 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") visszaadja NULL

@param api_url: Az API URL, amelyet a felhasználói információk lekérdezésére használunk.
@param user_id: A lekérdezni kívánt felhasználói azonosító.

@return A lekérdezéshez szükséges URL. Ha a felhasználói azonosító üres vagy érvénytelen, visszaadja a NULL-t. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    
    // Allocate memory for the new URL
    char* query_url = (char*)malloc(api_url_length + user_id_length + 2); // +2 for '/' and '\0'
    if (query_url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Construct the new URL
    strcpy(query_url, api_url);
    strcat(query_url, "/");
    strcat(query_url, user_id);

    return query_url;
}