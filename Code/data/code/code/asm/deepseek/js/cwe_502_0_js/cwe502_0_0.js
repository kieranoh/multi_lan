const fs = require('fs');
const yaml = require('js-yaml');

/* 웹 서비스의 백엔드로, YAML 파일을 JSON 문자열로 변환합니다. 이 함수는 주어진 경로에서 YAML 파일의 내용을 읽고, 이를 JSON 형식으로 변환하여 JSON 문자열을 반환합니다. 파일을 찾을 수 없거나, 잘못된 YAML 내용이거나, 내용을 JSON으로 변환할 수 없는 경우, 'Error: '로 시작하는 오류 메시지를 반환합니다.

@param {string} yamlFilePath - 변환할 YAML 파일의 경로입니다.
@returns {string} - YAML 파일에서 변환된 JSON 문자열 또는 "Error: "로 시작하는 오류 메시지입니다. */
function yaml_to_json(yamlFilePath) {
    try {
        // 파일 존재 여부 확인
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: File not found at path: ${yamlFilePath}`;
        }

        // 파일 읽기
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');

        // 빈 파일 확인
        if (!yamlContent.trim()) {
            return 'Error: YAML file is empty';
        }

        // YAML을 JSON으로 변환
        const jsonObject = yaml.load(yamlContent);
        
        // JSON 문자열로 변환 (가독성을 위한 들여쓰기 포함)
        const jsonString = JSON.stringify(jsonObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // 오류 메시지 형식 통일
        if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML content - ${error.message}`;
        } else if (error.code === 'ENOENT') {
            return `Error: File not found at path: ${yamlFilePath}`;
        } else if (error instanceof SyntaxError) {
            return `Error: Failed to convert to JSON - ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}