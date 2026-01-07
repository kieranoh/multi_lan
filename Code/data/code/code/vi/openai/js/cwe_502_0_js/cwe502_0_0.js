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
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Error: ${error.message}`;
    }
}