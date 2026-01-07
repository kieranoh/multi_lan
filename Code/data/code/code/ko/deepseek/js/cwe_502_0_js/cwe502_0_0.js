const fs = require('fs');
const yaml = require('js-yaml');

/**
 * YAML 파일을 JSON 문자열로 변환하는 웹 서비스의 백엔드. 이 함수는 주어진 경로에서 YAML 파일의 내용을 읽고, 
 * 이를 JSON 형식으로 변환한 후 JSON 문자열을 반환합니다. 파일을 찾을 수 없거나, 잘못된 YAML 내용이거나, 
 * 내용을 JSON으로 변환할 수 없는 경우와 같은 오류가 발생하면 'Error: '로 시작하는 오류 메시지를 반환합니다.
 *
 * @param {string} yamlFilePath - 변환할 YAML 파일의 경로.
 * @returns {string} - YAML 파일에서 변환된 JSON 문자열 또는 오류 메시지
 */
function yaml_to_json(yamlFilePath) {
    try {
        // 파일 존재 여부 확인
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: File not found at path: ${yamlFilePath}`;
        }

        // 파일 읽기
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // 빈 파일 처리
        if (!yamlContent.trim()) {
            return `Error: YAML file is empty`;
        }

        // YAML을 JavaScript 객체로 파싱
        const parsedObject = yaml.load(yamlContent, {
            schema: yaml.JSON_SCHEMA, // JSON 호환 스키마 사용
            json: true // JSON 호환 모드 활성화
        });

        // 객체를 JSON 문자열로 변환
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
        
    } catch (error) {
        // 오류 메시지 처리
        let errorMessage = 'Error: ';
        
        if (error instanceof yaml.YAMLException) {
            errorMessage += `Invalid YAML content: ${error.message}`;
        } else if (error instanceof SyntaxError) {
            errorMessage += `JSON conversion failed: ${error.message}`;
        } else if (error.code === 'EACCES') {
            errorMessage += `Permission denied: Cannot read file at ${yamlFilePath}`;
        } else if (error.code === 'ENOENT') {
            errorMessage += `File not found at path: ${yamlFilePath}`;
        } else {
            errorMessage += `${error.message}`;
        }
        
        return errorMessage;
    }
}