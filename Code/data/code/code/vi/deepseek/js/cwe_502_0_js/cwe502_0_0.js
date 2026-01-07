const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend cho một dịch vụ web chuyển đổi tệp YAML thành chuỗi json. Hàm này đọc nội dung của tệp YAML từ đường dẫn đã cho, chuyển đổi nó sang định dạng JSON và trả về chuỗi JSON. Nếu có bất kỳ lỗi nào, chẳng hạn như không tìm thấy tệp, nội dung YAML không hợp lệ hoặc nội dung không thể chuyển đổi sang JSON, hãy trả về thông báo lỗi bắt đầu bằng 'Error: '.
 *
 * @param {string} yamlFilePath - Đường dẫn đến tệp YAML cần chuyển đổi.
 * @returns {string} - Chuỗi JSON được chuyển đổi từ tệp YAML, hoặc một thông báo lỗi bắt đầu bằng "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Đọc nội dung tệp YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Phân tích nội dung YAML thành đối tượng JavaScript
        const parsedObject = yaml.load(yamlContent);
        
        // Chuyển đổi đối tượng thành chuỗi JSON
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // Xử lý các loại lỗi khác nhau
        if (error.code === 'ENOENT') {
            return `Error: File not found at path: ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML content: ${error.message}`;
        } else if (error instanceof TypeError) {
            return `Error: Failed to convert to JSON: ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}

module.exports = { yaml_to_json };