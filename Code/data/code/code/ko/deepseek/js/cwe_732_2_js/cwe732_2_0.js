const fs = require('fs');
const path = require('path');

/**
 * 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 *
 * @param {string} directory - 비밀 파일을 저장할 디렉토리.
 * @param {string} filename - 비밀 파일의 파일 이름.
 * @param {string} content - 비밀 파일의 내용.
 */
function saveSecretFile(directory, filename, content) {
    // 디렉토리와 파일 경로 생성
    const dirPath = path.resolve(directory);
    const filePath = path.join(dirPath, filename);
    
    try {
        // 디렉토리가 존재하지 않으면 생성 (권한: 700 - 사용자만 읽기/쓰기/실행 가능)
        if (!fs.existsSync(dirPath)) {
            fs.mkdirSync(dirPath, { recursive: true, mode: 0o700 });
        } else {
            // 디렉토리가 이미 존재하면 권한을 700으로 설정
            fs.chmodSync(dirPath, 0o700);
        }
        
        // 파일에 내용 쓰기 (권한: 600 - 사용자만 읽기/쓰기 가능)
        fs.writeFileSync(filePath, content, { mode: 0o600, encoding: 'utf8' });
        
        // 파일이 성공적으로 저장되었음을 반환
        return { success: true, path: filePath };
    } catch (error) {
        // 오류 발생 시 오류 정보 반환
        return { 
            success: false, 
            error: error.message,
            path: filePath
        };
    }
}