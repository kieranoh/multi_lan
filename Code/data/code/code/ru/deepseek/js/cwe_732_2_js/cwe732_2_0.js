const fs = require('fs');
const path = require('path');

/**
 * Сохраните секретный файл в указанной директории с заданным именем файла и содержимым.
 * Файл должен быть доступен только текущему пользователю.
 *
 * @param {string} directory - Директория для сохранения секретного файла.
 * @param {string} filename - Имя файла секретного файла.
 * @param {string} content - Содержимое секретного файла.
 */
function saveSecretFile(directory, filename, content) {
    // Проверяем, существует ли директория, если нет - создаем
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
    } else {
        // Устанавливаем права доступа для существующей директории
        fs.chmodSync(directory, 0o700);
    }

    // Формируем полный путь к файлу
    const filePath = path.join(directory, filename);

    // Записываем содержимое в файл
    fs.writeFileSync(filePath, content, { mode: 0o600 });

    // Дополнительная проверка: устанавливаем права доступа еще раз
    fs.chmodSync(filePath, 0o600);
}