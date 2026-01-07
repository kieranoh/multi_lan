#include <iostream>
#include <sstream>
#include <cstdlib>

std::string create_private_key() {
    const int key_length = 2048; // You can change the key length if needed
    std::ostringstream command;
    command << "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" << key_length;

    // Execute the command and capture the output
    FILE* pipe = popen(command.str().c_str(), "r");
    if (!pipe) {
        return nullptr; // Return NULL on error
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer; // Append the output to the result string
    }
    
    int return_code = pclose(pipe);
    if (return_code != 0) {
        return nullptr; // Return NULL if the command failed
    }

    return result; // Return the PEM formatted private key
}