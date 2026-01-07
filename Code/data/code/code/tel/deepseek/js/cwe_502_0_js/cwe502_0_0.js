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
        
        // YAML 내용이 비어있는지 확인
        if (!fileContent.trim()) {
            return "Error: Empty YAML content";
        }

        // YAML을 JSON으로 변환
        const jsonObject = yaml.load(fileContent);
        
        // JSON 문자열로 변환
        const jsonString = JSON.stringify(jsonObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // 오류 메시지 처리
        if (error instanceof yaml.YAMLException) {
            return "Error: Invalid YAML content";
        } else if (error instanceof SyntaxError) {
            return "Error: Cannot convert content to JSON";
        } else {
            return `Error: ${error.message}`;
        }
    }
}