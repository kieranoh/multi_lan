#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t* jwt = NULL;
    char* json = NULL;

    // Initialize JWT
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) != 0) {
        // If decoding fails, return an empty JSON object
        return "{}";
    }

    // Convert JWT claims to a JSON string
    json = jwt_get_grant(jwt, "claims"); // Get the claims as a JSON string

    // Cleanup
    jwt_free(jwt);

    // Return the JSON string or an empty JSON object if claims are NULL
    return json ? json : "{}";
}