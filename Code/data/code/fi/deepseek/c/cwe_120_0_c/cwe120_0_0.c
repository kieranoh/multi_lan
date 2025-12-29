#include <stdio.h>
#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Tarkistetaan, että puskuri ja käyttäjänimi ovat kelvollisia
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    // Varmistetaan, että userName_size on järkevä arvo
    int actual_userName_size = 0;
    if (userName_size > 0) {
        actual_userName_size = userName_size;
    } else {
        // Jos userName_size ei ole annettu, lasketaan pituus itse
        actual_userName_size = (int)strlen(userName);
    }
    
    // Lasketaan tarvittava tilauspituus: "Onnittelut, " + käyttäjänimi + "!" + lopetusmerkki
    int required_size = 12 + actual_userName_size + 2; // 12 = "Onnittelut, ", 2 = "!" + '\0'
    
    // Tarkistetaan, että puskuri on riittävän suuri
    if (buffer_size < required_size) {
        // Jos puskuri on liian pieni, kirjoitetaan mahdollisimman paljon
        if (buffer_size > 0) {
            // Kopioidaan "Onnittelut, "
            strncpy(buffer, "Onnittelut, ", buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
            
            // Jos tilaa riittää, lisätään osa käyttäjänimestä
            int current_len = (int)strlen(buffer);
            int remaining_space = buffer_size - current_len - 1; // -1 lopetusmerkille
            
            if (remaining_space > 0) {
                // Kopioidaan osa käyttäjänimestä
                int copy_len = actual_userName_size;
                if (copy_len > remaining_space) {
                    copy_len = remaining_space;
                }
                
                strncat(buffer, userName, copy_len);
                current_len = (int)strlen(buffer);
                remaining_space = buffer_size - current_len - 1;
                
                // Jos tilaa riittää, lisätään huutomerkki
                if (remaining_space > 0) {
                    strncat(buffer, "!", 1);
                }
            }
        }
    } else {
        // Puskuri on riittävän suuri, kirjoitetaan koko viesti
        strcpy(buffer, "Onnittelut, ");
        strncat(buffer, userName, actual_userName_size);
        strcat(buffer, "!");
    }
}