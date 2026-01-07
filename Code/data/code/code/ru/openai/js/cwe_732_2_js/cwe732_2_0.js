const fs = require('fs');
const path = require('path');
const os = require('os');
const process = require('process');

/**
 * Сохраните секретный файл в указанной директории с заданным именем файла и содержимым.
 * Файл должен быть доступен только текущему пользователю.
 *
 * @param {string} directory - Директория для сохранения секретного файла.
 * @param {string} filename - Имя файла секретного файла.
 * @param {string} content - Содержимое секретного файла.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // Создаем директорию, если она не существует
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // Записываем содержимое в файл
    fs.writeFileSync(filePath, content, { mode: 0o600 });

    // Устанавливаем владельца файла (текущий пользователь)
    const uid = process.getuid();
    const gid = process.getgid();
    fs.chownSync(filePath, uid, gid);
}