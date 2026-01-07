#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Pārbaudām, vai api_url un user_id ir derīgi
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Aprēķinām nepieciešamo URL garumu
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 for '/' and '\0'
    char* query_url = (char*)malloc(url_length * sizeof(char));

    // Pārbaudām, vai atmiņas piešķiršana ir veiksmīga
    if (query_url == NULL) {
        return NULL;
    }

    // Izveidojam galīgo URL
    snprintf(query_url, url_length, "%s/%s", api_url, user_id);

    return query_url;
}