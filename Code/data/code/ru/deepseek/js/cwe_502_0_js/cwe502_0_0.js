const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Проверяем, существует ли файл
        if (!fs.existsSync(yamlFilePath)) {
            return 'Ошибка: Файл не найден';
        }

        // Считываем содержимое файла
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Проверяем, не пустой ли файл
        if (!yamlContent.trim()) {
            return 'Ошибка: Файл пуст';
        }

        // Парсим YAML
        const parsedYaml = yaml.load(yamlContent, {
            filename: yamlFilePath,
            onWarning: (warning) => {
                // Можно логировать предупреждения, но не прерывать выполнение
                console.warn('YAML предупреждение:', warning);
            }
        });

        // Проверяем, удалось ли распарсить YAML
        if (parsedYaml === undefined) {
            return 'Ошибка: Не удалось распарсить YAML содержимое';
        }

        // Конвертируем в строку JSON
        const jsonString = JSON.stringify(parsedYaml, null, 2);
        
        return jsonString;

    } catch (error) {
        // Обрабатываем различные типы ошибок
        if (error instanceof yaml.YAMLException) {
            return `Ошибка: Недопустимое содержимое YAML - ${error.message}`;
        } else if (error.code === 'ENOENT') {
            return 'Ошибка: Файл не найден';
        } else if (error.code === 'EACCES') {
            return 'Ошибка: Нет доступа к файлу';
        } else if (error instanceof SyntaxError) {
            return `Ошибка: Не удалось конвертировать в JSON - ${error.message}`;
        } else {
            return `Ошибка: ${error.message}`;
        }
    }
}