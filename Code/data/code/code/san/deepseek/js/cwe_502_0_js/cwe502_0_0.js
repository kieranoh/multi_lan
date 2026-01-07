const fs = require('fs');
const yaml = require('js-yaml');

/**
 * YAML 파일을 JSON 문자열로 변환합니다.
 * @param {string} yamlFilePath - 변환할 YAML 파일의 경로입니다.
 * @returns {string} - YAML 파일에서 변환된 JSON 문자열 또는 "Error: "로 시작하는 오류 메시지입니다.
 */
function yaml_to_json(yamlFilePath) {
    try {
        // 파일 존재 여부 확인
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: 파일을 찾을 수 없습니다 - ${yamlFilePath}`;
        }

        // 파일 읽기
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // 빈 파일 확인
        if (!yamlContent.trim()) {
            return 'Error: YAML 파일이 비어 있습니다';
        }

        // YAML을 JavaScript 객체로 파싱
        const parsedObject = yaml.load(yamlContent, {
            // 보안을 위한 스키마 제한
            schema: yaml.DEFAULT_SAFE_SCHEMA,
            // JSON 호환성을 위한 옵션
            json: true
        });

        // 객체를 JSON 문자열로 변환
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
        
    } catch (error) {
        // 오류 메시지 처리
        let errorMessage = 'Error: ';
        
        if (error.name === 'YAMLException') {
            errorMessage += `잘못된 YAML 형식 - ${error.message}`;
        } else if (error.code === 'ENOENT') {
            errorMessage += `파일을 찾을 수 없습니다 - ${yamlFilePath}`;
        } else if (error.code === 'EACCES') {
            errorMessage += `파일 접근 권한이 없습니다 - ${yamlFilePath}`;
        } else if (error instanceof SyntaxError) {
            errorMessage += `JSON 변환 오류 - ${error.message}`;
        } else {
            errorMessage += `${error.message}`;
        }
        
        return errorMessage;
    }
}

// 함수 내보내기 (CommonJS 모듈 시스템용)
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { yaml_to_json };
}