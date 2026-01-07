const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // 파일 존재 여부 확인
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: File not found at path: ${yamlFilePath}`;
        }

        // 파일 읽기
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        if (!yamlContent.trim()) {
            return 'Error: YAML file is empty';
        }

        // YAML을 JSON으로 변환
        const jsonObject = yaml.load(yamlContent);
        
        if (jsonObject === undefined) {
            return 'Error: Invalid YAML content';
        }

        // JSON 문자열로 변환
        const jsonString = JSON.stringify(jsonObject, null, 2);
        return jsonString;

    } catch (error) {
        // 오류 메시지 처리
        if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML format - ${error.message}`;
        } else if (error.code === 'ENOENT') {
            return `Error: File not found at path: ${yamlFilePath}`;
        } else if (error.code === 'EACCES') {
            return `Error: Permission denied for file: ${yamlFilePath}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}