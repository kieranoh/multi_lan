const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Функция конвертирует файл YAML в строку JSON.
 *
 * @param {string} yamlFilePath - Путь к файлу YAML для конвертации.
 * @returns {string} - Строка JSON, конвертированная из файла YAML, или сообщение об ошибке, начинающееся с "Ошибка: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Считываем содержимое файла YAML
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Конвертируем YAML в объект JavaScript
        const data = yaml.load(fileContents);
        
        // Конвертируем объект в строку JSON
        return JSON.stringify(data);
    } catch (error) {
        // Возвращаем сообщение об ошибке
        return `Ошибка: ${error.message}`;
    }
}