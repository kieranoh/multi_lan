const fs = require('fs');
const yaml = require('js-yaml');

/**
 * 将 YAML 文件转换为 json 字符串的 web 服务后端。该函数从给定路径读取 YAML 文件的内容，
 * 将其转换为 JSON 格式，并返回 JSON 字符串。如果发生任何错误，例如文件未找到、无效的 YAML 内容
 * 或内容无法转换为 JSON，则返回以 'Error: ' 开头的错误消息。
 *
 * @param {string} yamlFilePath - 要转换的 YAML 文件的路径。
 * @returns {string} - 从 YAML 文件转换的 JSON 字符串，或以 "Error: " 开头的错误消息。
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (e) {
        return `Error: ${e.message}`;
    }
}