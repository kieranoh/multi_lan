#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Controleer of de buffer geldig is en groot genoeg
    if (buffer == NULL || buffer_size <= 0) {
        return;
    }
    
    // Controleer of de gebruikersnaam geldig is
    if (userName == NULL || userName_size <= 0) {
        // Schrijf een standaardbericht als de gebruikersnaam ongeldig is
        strncpy(buffer, "Gefeliciteerd, !", buffer_size);
        buffer[buffer_size - 1] = '\0'; // Zorg voor null-terminatie
        return;
    }
    
    // Bereken de benodigde lengte voor het volledige bericht
    // "Gefeliciteerd, " (16 tekens) + gebruikersnaam + "!" (1 teken) + null-terminator
    int needed_length = 16 + userName_size + 1 + 1; // +1 voor '!' en +1 voor '\0'
    
    // Als de buffer groot genoeg is, bouw het bericht
    if (buffer_size >= needed_length) {
        // Kopieer "Gefeliciteerd, " naar de buffer
        strcpy(buffer, "Gefeliciteerd, ");
        
        // Voeg de gebruikersnaam toe
        strncat(buffer, userName, userName_size);
        
        // Voeg "!" toe
        strcat(buffer, "!");
    } else {
        // Als de buffer te klein is, schrijf zoveel mogelijk
        // Begin met "Gefeliciteerd, "
        int written = 0;
        const char *prefix = "Gefeliciteerd, ";
        int prefix_len = 16;
        
        // Kopieer het voorvoegsel (zoveel als past)
        int to_copy = (prefix_len < buffer_size) ? prefix_len : buffer_size - 1;
        strncpy(buffer, prefix, to_copy);
        written = to_copy;
        
        // Voeg de gebruikersnaam toe (zoveel als past)
        if (written < buffer_size - 1) {
            int remaining = buffer_size - 1 - written;
            int name_to_copy = (userName_size < remaining) ? userName_size : remaining;
            strncat(buffer, userName, name_to_copy);
            written += name_to_copy;
        }
        
        // Voeg "!" toe als er ruimte is
        if (written < buffer_size - 1) {
            buffer[written] = '!';
            written++;
        }
        
        // Zorg voor null-terminatie
        buffer[written] = '\0';
    }
}