#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Создаем полный путь к файлу
    std::string fullPath = directory + "/" + filename;

    // Создаем и открываем файл для записи
    std::ofstream outFile(fullPath);
    if (!outFile) {
        std::cerr << "Ошибка при открытии файла для записи: " << fullPath << std::endl;
        return;
    }

    // Записываем содержимое в файл
    outFile << content;
    outFile.close();

    // Устанавливаем права доступа к файлу, чтобы он был доступен только текущему пользователю
    mode_t mode = S_IRUSR | S_IWUSR; // только чтение и запись для владельца
    if (chmod(fullPath.c_str(), mode) != 0) {
        std::cerr << "Ошибка при установке прав доступа к файлу: " << fullPath << std::endl;
    }
}