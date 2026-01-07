const fs = require('fs');
const path = require('path');

/**
 * 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 * 
 * @param {string} directory - 비밀 파일을 저장할 디렉토리.
 * @param {string} filename - 비밀 파일의 파일 이름.
 * @param {string} content - 비밀 파일의 내용.
 * @returns {Promise<void>} - 파일 저장 완료 시 해결되는 Promise.
 * @throws {Error} - 디렉토리 생성 실패 또는 파일 쓰기 실패 시 예외 발생.
 */
function saveSecretFile(directory, filename, content) {
    return new Promise((resolve, reject) => {
        try {
            // 디렉토리 경로와 파일 경로 생성
            const dirPath = path.resolve(directory);
            const filePath = path.join(dirPath, filename);

            // 디렉토리가 존재하지 않으면 생성 (재귀적으로)
            if (!fs.existsSync(dirPath)) {
                fs.mkdirSync(dirPath, { recursive: true, mode: 0o700 });
            } else {
                // 디렉토리가 이미 존재하면 권한을 700으로 설정
                fs.chmodSync(dirPath, 0o700);
            }

            // 파일 내용을 동기적으로 쓰기
            fs.writeFileSync(filePath, content, {
                encoding: 'utf8',
                mode: 0o600  // 현재 사용자만 읽기/쓰기 가능 (rw-------)
            });

            console.log(`비밀 파일이 성공적으로 저장되었습니다: ${filePath}`);
            resolve();
        } catch (error) {
            console.error('비밀 파일 저장 중 오류 발생:', error.message);
            reject(error);
        }
    });
}

// 사용 예시 (주석 처리됨):
// saveSecretFile('./secrets', 'mySecret.txt', '이것은 비밀 내용입니다.')
//     .then(() => console.log('파일 저장 완료'))
//     .catch(err => console.error('오류:', err));

// 비동기/await 사용 예시 (주석 처리됨):
// async function example() {
//     try {
//         await saveSecretFile('./secrets', 'mySecret.txt', '이것은 비밀 내용입니다.');
//         console.log('파일 저장 완료');
//     } catch (error) {
//         console.error('오류:', error);
//     }
// }
// example();