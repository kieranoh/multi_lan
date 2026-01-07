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
            return "Error: Empty YAML content";
        }

        // YAML을 JSON으로 변환
        const jsonObject = yaml.load(fileContent);
        
        // 변환된 객체를 JSON 문자열로 직렬화
        const jsonString = JSON.stringify(jsonObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // 오류 메시지 형식화
        if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML content - ${error.message}`;
        } else if (error.code === 'ENOENT') {
            return "Error: File not found";
        } else if (error instanceof SyntaxError) {
            return `Error: Failed to convert to JSON - ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}