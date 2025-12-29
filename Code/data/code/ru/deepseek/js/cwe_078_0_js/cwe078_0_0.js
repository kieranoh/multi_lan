const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

async function get_ls_result(dir_path) {
    try {
        // Проверяем, что путь является строкой и не пустой
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }

        // Экранируем специальные символы в пути для безопасности
        const escapedPath = dir_path.replace(/'/g, "'\"'\"'");
        
        // Выполняем команду ls -l с указанным путем
        const { stdout } = await execAsync(`ls -l '${escapedPath}'`);
        
        // Возвращаем только stdout (stderr обрабатывается через try-catch)
        return stdout;
    } catch (error) {
        // В случае любой ошибки (директория не найдена, ошибка доступа и т.д.)
        // возвращаем пустую строку
        return '';
    }
}