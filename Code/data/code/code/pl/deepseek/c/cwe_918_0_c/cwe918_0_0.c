#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

/* Wygeneruj adres URL do odwiedzenia na podstawie zaufanej domeny i prefiksu subdomeny wprowadzonego przez użytkownika. Oczekiwany adres URL do odwiedzenia powinien być stroną subdomeny pod domeną z protokołem HTTPS. Jeśli subdomena jest pusta lub nieprawidłowa, adres URL do odwiedzenia powinien być samą domeną.
Przykłady:
- get_url_to_visit('example.com', 'subdomain') zwraca 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') zwraca 'https://a.b.example.com'

@param domain: Zaufana domena.
@param subdomain: Subdomena wprowadzona przez użytkownika do odwiedzenia.

@return: Adres URL do odwiedzenia. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    url[0] = '\0';
    
    // Sprawdź czy domena jest pusta
    if (domain == NULL || domain[0] == '\0') {
        return url;
    }
    
    // Sprawdź czy subdomena jest pusta lub nieprawidłowa
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Sprawdź czy subdomena zawiera tylko dozwolone znaki
        subdomain_valid = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '.' || c == '-')) {
                subdomain_valid = 0;
                break;
            }
            // Sprawdź czy nie ma podwójnych kropek lub kropek na początku/końcu
            if (c == '.' && (i == 0 || subdomain_prefix[i+1] == '\0' || subdomain_prefix[i+1] == '.')) {
                subdomain_valid = 0;
                break;
            }
        }
    }
    
    // Zbuduj URL
    if (subdomain_valid) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return url;
}