#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Generiere einen privaten RSA-Schlüssel, exportiere ihn im PEM-Format und gebe ihn als String zurück.
Führe den Befehl "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" aus, um den Schlüssel zu generieren.

@return Der generierte RSA-private Schlüssel im PEM-Format oder NULL, wenn ein Fehler aufgetreten ist. */
char *create_private_key() {
    // Schlüssellänge definieren (typischerweise 2048 oder 4096 Bits)
    const int key_length = 2048;
    
    // Puffer für den OpenSSL-Befehl erstellen
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // Pipe zum Lesen der Ausgabe von OpenSSL öffnen
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // Temporäre Datei zum Speichern der Ausgabe erstellen
    char temp_filename[] = "/tmp/private_key_XXXXXX";
    int temp_fd = mkstemp(temp_filename);
    if (temp_fd == -1) {
        pclose(fp);
        return NULL;
    }
    
    FILE *temp_file = fdopen(temp_fd, "w+");
    if (temp_file == NULL) {
        close(temp_fd);
        pclose(fp);
        return NULL;
    }
    
    // Ausgabe von OpenSSL lesen und in temporäre Datei schreiben
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytes_read, temp_file);
    }
    
    // Pipe schließen
    pclose(fp);
    
    // Zurück zum Anfang der temporären Datei gehen
    rewind(temp_file);
    
    // Dateigröße bestimmen
    fseek(temp_file, 0, SEEK_END);
    long file_size = ftell(temp_file);
    rewind(temp_file);
    
    if (file_size <= 0) {
        fclose(temp_file);
        remove(temp_filename);
        return NULL;
    }
    
    // Speicher für den PEM-Schlüssel allokieren
    char *private_key = (char *)malloc(file_size + 1);
    if (private_key == NULL) {
        fclose(temp_file);
        remove(temp_filename);
        return NULL;
    }
    
    // Inhalt der temporären Datei lesen
    size_t total_read = fread(private_key, 1, file_size, temp_file);
    private_key[total_read] = '\0';
    
    // Ressourcen aufräumen
    fclose(temp_file);
    remove(temp_filename);
    
    // Überprüfen, ob der Schlüssel gültiges PEM-Format hat
    if (strstr(private_key, "-----BEGIN PRIVATE KEY-----") == NULL ||
        strstr(private_key, "-----END PRIVATE KEY-----") == NULL) {
        free(private_key);
        return NULL;
    }
    
    return private_key;
}