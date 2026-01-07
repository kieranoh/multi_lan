const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // 파일 존재 여부 확인
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: File not found at path: ${yamlFilePath}`;
        }

        // YAML 파일 읽기
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        if (!yamlContent.trim()) {
            return `Error: YAML file is empty`;
        }

        // YAML을 JSON으로 변환
        const jsonObject = yaml.load(yamlContent);
        
        // JSON 문자열로 변환
        const jsonString = JSON.stringify(jsonObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // 오류 메시지 처리
        if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML content - ${error.message}`;
        } else if (error instanceof SyntaxError) {
            return `Error: Failed to convert to JSON - ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}