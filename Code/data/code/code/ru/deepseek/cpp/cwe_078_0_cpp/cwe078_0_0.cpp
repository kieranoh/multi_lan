#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
    #include <tchar.h>
    #include <stdio.h>
    #include <strsafe.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <fcntl.h>
    #include <errno.h>
#endif

std::string get_ls_result(const std::string &dir_path) {
    std::string result;
    
    // Проверяем, что путь не пустой
    if (dir_path.empty()) {
        return "";
    }
    
#ifdef _WIN32
    // Windows реализация
    std::string command = "cmd /c \"cd /d \"" + dir_path + "\" 2>nul && dir /l 2>nul\"";
    
    // Создаем pipe для чтения вывода команды
    HANDLE hPipeRead, hPipeWrite;
    SECURITY_ATTRIBUTES saAttr = {sizeof(SECURITY_ATTRIBUTES)};
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;
    
    if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0)) {
        return "";
    }
    
    // Устанавливаем наследуемый флаг для дескриптора записи
    if (!SetHandleInformation(hPipeWrite, HANDLE_FLAG_INHERIT, 0)) {
        CloseHandle(hPipeRead);
        CloseHandle(hPipeWrite);
        return "";
    }
    
    // Создаем процесс
    PROCESS_INFORMATION piProcInfo = {0};
    STARTUPINFOA siStartInfo = {sizeof(STARTUPINFOA)};
    siStartInfo.hStdError = hPipeWrite;
    siStartInfo.hStdOutput = hPipeWrite;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
    
    std::string cmdLine = command;
    
    if (!CreateProcessA(NULL, 
                       const_cast<LPSTR>(cmdLine.c_str()),
                       NULL,
                       NULL,
                       TRUE,
                       CREATE_NO_WINDOW,
                       NULL,
                       NULL,
                       &siStartInfo,
                       &piProcInfo)) {
        CloseHandle(hPipeRead);
        CloseHandle(hPipeWrite);
        return "";
    }
    
    CloseHandle(hPipeWrite);
    
    // Читаем вывод из pipe
    DWORD dwRead;
    CHAR chBuf[4096];
    BOOL bSuccess = FALSE;
    
    while (true) {
        bSuccess = ReadFile(hPipeRead, chBuf, sizeof(chBuf) - 1, &dwRead, NULL);
        if (!bSuccess || dwRead == 0) {
            break;
        }
        chBuf[dwRead] = '\0';
        result += chBuf;
    }
    
    // Ждем завершения процесса
    WaitForSingleObject(piProcInfo.hProcess, INFINITE);
    
    DWORD exitCode;
    GetExitCodeProcess(piProcInfo.hProcess, &exitCode);
    
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(hPipeRead);
    
    // Если команда завершилась с ошибкой, возвращаем пустую строку
    if (exitCode != 0) {
        return "";
    }
    
#else
    // Unix/Linux/macOS реализация
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Создаем pipe
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return "";
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        // Ошибка при создании процесса
        close(pipefd[0]);
        close(pipefd[1]);
        return "";
    }
    
    if (pid == 0) {
        // Дочерний процесс
        close(pipefd[0]); // Закрываем конец для чтения
        
        // Перенаправляем stdout в pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Выполняем команду
        execl("/bin/sh", "sh", "-c", command.c_str(), (char*)NULL);
        
        // Если execl вернулся, значит произошла ошибка
        _exit(127);
    } else {
        // Родительский процесс
        close(pipefd[1]); // Закрываем конец для записи
        
        // Читаем вывод из pipe
        char buffer[4096];
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            result += buffer;
        }
        
        close(pipefd[0]);
        
        // Ждем завершения дочернего процесса
        int status;
        waitpid(pid, &status, 0);
        
        // Проверяем статус завершения
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
                // Команда завершилась с ошибкой
                return "";
            }
        } else {
            // Процесс был завершен сигналом
            return "";
        }
    }
#endif
    
    // Удаляем завершающие пробелы и символы новой строки
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r' || result.back() == ' ')) {
        result.pop_back();
    }
    
    return result;
}