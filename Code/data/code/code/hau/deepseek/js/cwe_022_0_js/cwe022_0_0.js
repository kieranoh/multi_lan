function read_file_from_dir(filename, dir_path) {
    const fs = require('fs');
    const path = require('path');
    
    try {
        // 경로 조합 및 정규화
        const filePath = path.join(dir_path, filename);
        
        // 파일 존재 여부 확인
        if (!fs.existsSync(filePath)) {
            return '';
        }
        
        // 파일 읽기 (동기 방식으로 처리)
        const content = fs.readFileSync(filePath, 'utf-8');
        return content;
    } catch (error) {
        // 모든 오류(파일 없음, 권한 오류, 읽기 오류 등)에 대해 빈 문자열 반환
        return '';
    }
}