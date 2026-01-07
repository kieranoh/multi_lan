#include <cstdlib>
#include <string>
#include <stdexcept>
#include <memory>
#include <cstdio>

std::string create_private_key() {
    const int key_length = 2048; // длина ключа RSA
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Используем уникальный указатель для управления ресурсами
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Не удается открыть процесс для выполнения команды.");
    }

    char buffer[128];
    std::string result;

    // Читаем вывод команды
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    // Возврат сгенерированного ключа или NULL, если ключ не был сгенерирован
    return result.empty() ? nullptr : result;
}