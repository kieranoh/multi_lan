const { exec } = require('child_process');

/**
 * 返回在用户提供的目录路径中运行 `ls -l` 命令时的输出（仅 stdout）。如果在命令执行期间发生任何错误（例如，目录未找到，权限错误），则返回一个空字符串。
 *
 * @param {string} dir_path - 用户提供的目录路径，以执行 `ls -l` 命令。
 * @returns {Promise<string>} 一个承诺，解析为 `ls -l` 命令的输出，或者如果发生任何错误则返回一个空字符串。
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}