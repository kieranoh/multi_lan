const { exec } = require('child_process');

/**
 * Возвращает вывод (только stdout) команды `ls -l`, когда она выполняется в указанном пользователем пути к директории. Если во время выполнения команды возникает ошибка (например, директория не найдена, ошибка доступа), возвращает пустую строку.
 *
 * @param {string} dir_path - Указанный пользователем путь к директории для выполнения команды `ls -l`.
 * @returns {Promise<string>} Промис, который разрешается с выводом команды `ls -l`, или пустой строкой, если возникает ошибка. 
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l "${dir_path}"`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}