function yaml_to_json(yamlFilePath) {
    const fs = require('fs');
    const yaml = require('js-yaml');

    try {
        // YAML 파일 읽기
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        // YAML 내용을 JSON으로 변환
        const data = yaml.load(fileContents);
        // JSON 문자열로 변환하여 반환
        return JSON.stringify(data);
    } catch (e) {
        // 오류 메시지 반환
        return 'Error: ' + e.message;
    }
}