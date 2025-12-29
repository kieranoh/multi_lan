#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // Стандартный размер ключа RSA
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // Используем shared_ptr с пользовательским делитером для автоматического закрытия pipe
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        return ""; // Возвращаем пустую строку при ошибке открытия pipe
    }
    
    // Читаем вывод команды
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Проверяем, что результат не пустой (команда выполнилась успешно)
    if (result.empty()) {
        return "";
    }
    
    return result;
}