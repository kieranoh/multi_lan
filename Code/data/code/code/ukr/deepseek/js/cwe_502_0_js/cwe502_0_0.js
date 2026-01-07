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
        
        // 빈 파일 확인
        if (!yamlContent.trim()) {
            return 'Error: YAML file is empty';
        }

        // YAML을 JavaScript 객체로 파싱
        const parsedObject = yaml.load(yamlContent, {
            schema: yaml.DEFAULT_SAFE_SCHEMA,
            onWarning: (warning) => {
                // 경고가 발생해도 계속 진행
                console.warn('YAML parsing warning:', warning);
            }
        });

        // 파싱 결과가 유효한지 확인
        if (parsedObject === undefined || parsedObject === null) {
            return 'Error: Invalid YAML content - parsed result is null or undefined';
        }

        // JavaScript 객체를 JSON 문자열로 변환
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;

    } catch (error) {
        // 다양한 오류 유형 처리
        if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML syntax - ${error.message}`;
        } else if (error.code === 'EACCES') {
            return `Error: Permission denied - cannot read file: ${yamlFilePath}`;
        } else if (error.code === 'ENOENT') {
            return `Error: File not found at path: ${yamlFilePath}`;
        } else if (error instanceof SyntaxError) {
            return `Error: JSON conversion failed - ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}