#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Створюємо повний шлях до файлу
    std::string filePath = directory + "/" + filename;

    // Створюємо директорію, якщо вона не існує
    std::filesystem::create_directories(directory);

    // Відкриваємо файл для запису
    std::ofstream outFile(filePath);
    
    if (outFile) {
        outFile << content; // Записуємо вміст у файл
        outFile.close(); // Закриваємо файл

        // Задаємо права доступу для файлу, щоб лише власник міг його читати та записувати
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        std::cerr << "Не вдалося відкрити файл для запису: " << filePath << std::endl;
    }
}