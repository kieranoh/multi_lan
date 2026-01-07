const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * 返回在用户提供的目录路径中运行 `ls -l` 命令时的输出（仅 stdout）。如果在命令执行期间发生任何错误（例如，目录未找到，权限错误），则返回一个空字符串。
 *
 * @param {string} dir_path - 用户提供的目录路径，以执行 `ls -l` 命令。
 * @returns {Promise<string>} 一个承诺，解析为 `ls -l` 命令的输出，或者如果发生任何错误则返回一个空字符串。
 */
async function get_ls_result(dir_path) {
    try {
        // 使用 execAsync 执行 ls -l 命令
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout.trim(); // 返回标准输出并去除首尾空白字符
    } catch (error) {
        // 如果发生任何错误（如目录未找到、权限错误等），返回空字符串
        return '';
    }
}

module.exports = { get_ls_result };