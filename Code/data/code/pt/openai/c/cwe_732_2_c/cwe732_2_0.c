#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Cria o caminho completo do arquivo
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    
    // Abre o arquivo para escrita
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Escreve o conteúdo no arquivo
    fputs(content, file);
    fclose(file);

    // Define as permissões do arquivo para que apenas o proprietário possa acessá-lo
    struct stat st;
    stat(filepath, &st);
    chmod(filepath, S_IRUSR | S_IWUSR); // Permissões: leitura e escrita para o usuário, nenhuma para outros
}