const fs = require('fs');
const yaml = require('js-yaml');

/**
 * 将 YAML 文件转换为 json 字符串的 web 服务后端。该函数从给定路径读取 YAML 文件的内容，将其转换为 JSON 格式，并返回 JSON 字符串。如果发生任何错误，例如文件未找到、无效的 YAML 内容或内容无法转换为 JSON，则返回以 'Error: ' 开头的错误消息。
 *
 * @param {string} yamlFilePath - 要转换的 YAML 文件的路径。
 * @returns {string} - 从 YAML 文件转换的 JSON 字符串，或以 "Error: " 开头的错误消息。
 */
function yaml_to_json(yamlFilePath) {
    try {
        // 检查文件路径是否为空或无效
        if (!yamlFilePath || typeof yamlFilePath !== 'string') {
            return 'Error: 无效的文件路径';
        }

        // 读取 YAML 文件内容
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');

        // 检查文件内容是否为空
        if (!yamlContent.trim()) {
            return 'Error: YAML 文件为空';
        }

        // 将 YAML 内容解析为 JavaScript 对象
        const parsedObject = yaml.load(yamlContent, {
            // 使用安全模式加载，避免执行任意代码
            schema: yaml.SAFE_SCHEMA
        });

        // 将 JavaScript 对象转换为 JSON 字符串
        const jsonString = JSON.stringify(parsedObject, null, 2);

        return jsonString;
    } catch (error) {
        // 根据错误类型返回相应的错误消息
        if (error.code === 'ENOENT') {
            return 'Error: 文件未找到';
        } else if (error instanceof yaml.YAMLException) {
            return `Error: 无效的 YAML 内容 - ${error.message}`;
        } else if (error instanceof TypeError && error.message.includes('stringify')) {
            return 'Error: 内容无法转换为 JSON';
        } else {
            return `Error: ${error.message}`;
        }
    }
}