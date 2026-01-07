const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // 파일 존재 여부 확인
        if (!fs.existsSync(yamlFilePath)) {
            return "Error: File not found";
        }

        // 파일 읽기
        const fileContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // 빈 파일 확인
        if (!fileContent.trim()) {
            return "Error: Empty YAML file";
        }

        // YAML을 JavaScript 객체로 파싱
        const yamlObject = yaml.load(fileContent);
        
        // 객체를 JSON 문자열로 변환
        const jsonString = JSON.stringify(yamlObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // 오류 메시지 처리
        if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML format - ${error.message}`;
        } else if (error.code === 'EACCES') {
            return "Error: Permission denied";
        } else if (error.code === 'ENOENT') {
            return "Error: File not found";
        } else if (error.code === 'EISDIR') {
            return "Error: Path is a directory, not a file";
        } else {
            return `Error: ${error.message}`;
        }
    }
}