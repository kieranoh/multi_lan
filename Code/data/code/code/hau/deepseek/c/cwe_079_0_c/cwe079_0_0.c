char* get_welcome_message(const char* username) {
    /* Berechne die Länge der Nachricht:
       "Willkommen, " (12 Zeichen) + username + "!" (1 Zeichen) + Nullterminierung (1 Zeichen) */
    int len = 12 + strlen(username) + 1 + 1;
    
    /* Allokiere Speicher für die Nachricht */
    char* message = (char*)malloc(len * sizeof(char));
    
    /* Überprüfe, ob die Speicherallokation erfolgreich war */
    if (message == NULL) {
        return NULL;  /* Rückgabe von NULL bei Speicherfehler */
    }
    
    /* Erstelle die Willkommensnachricht */
    strcpy(message, "Willkommen, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}