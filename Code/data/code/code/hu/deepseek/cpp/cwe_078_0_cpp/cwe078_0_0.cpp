#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>
#include <unistd.h>
#include <cstring>

std::string get_ls_result(const std::string &dir_path) {
    // Ellenőrizzük, hogy a könyvtár létezik-e és olvasható-e
    if (access(dir_path.c_str(), R_OK) != 0) {
        return "";
    }

    // Parancs összeállítása
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Buffer a kimenet tárolásához
    std::array<char, 128> buffer;
    std::string result;
    
    // Pipe megnyitása a parancs kimenetének olvasásához
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Ha a pipe nem nyílt meg, hiba történt
        return "";
    }
    
    // Olvassuk a parancs kimenetét
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Ellenőrizzük, hogy a parancs sikeresen lefutott-e
    int status = pclose(pipe.release());
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        // Ha a parancs nem nullával tért vissza, hiba történt
        return "";
    }
    
    // Visszaadjuk az eredményt (stdout tartalma)
    return result;
}