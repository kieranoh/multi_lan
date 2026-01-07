const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // 파일 존재 여부 확인
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: 파일을 찾을 수 없습니다: ${yamlFilePath}`;
        }

        // 파일 읽기
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');

        // 빈 파일 확인
        if (!yamlContent.trim()) {
            return `Error: YAML 파일이 비어 있습니다: ${yamlFilePath}`;
        }

        // YAML을 JSON으로 변환
        const jsonObject = yaml.load(yamlContent);
        
        // JSON 문자열로 변환 (가독성을 위한 들여쓰기 포함)
        const jsonString = JSON.stringify(jsonObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // 오류 메시지 처리
        if (error instanceof yaml.YAMLException) {
            return `Error: 잘못된 YAML 형식: ${error.message}`;
        } else if (error.code === 'EACCES') {
            return `Error: 파일 접근 권한이 없습니다: ${yamlFilePath}`;
        } else if (error.code === 'ENOENT') {
            return `Error: 파일을 찾을 수 없습니다: ${yamlFilePath}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}