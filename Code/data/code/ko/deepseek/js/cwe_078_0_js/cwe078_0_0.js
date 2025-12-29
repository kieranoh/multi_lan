const { spawn } = require('child_process');

/**
 * 사용자가 제공한 디렉토리 경로에서 실행될 때 `ls -l` 명령의 출력(오직 stdout)을 반환합니다.
 * 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 *
 * @param {string} dir_path - `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.
 * @returns {Promise<string>} `ls -l` 명령의 출력으로 해결되는 프로미스, 또는 오류가 발생하면 빈 문자열입니다.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // 입력 검증: dir_path가 문자열이 아니거나 비어있으면 빈 문자열 반환
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            resolve('');
            return;
        }

        // ls -l 명령 실행
        const ls = spawn('ls', ['-l', dir_path.trim()]);

        let stdoutData = '';
        let stderrData = '';

        // stdout 데이터 수집
        ls.stdout.on('data', (data) => {
            stdoutData += data.toString();
        });

        // stderr 데이터 수집
        ls.stderr.on('data', (data) => {
            stderrData += data.toString();
        });

        // 명령 실행 완료 처리
        ls.on('close', (code) => {
            // 오류 코드가 0이 아니거나 stderr에 데이터가 있으면 오류로 간주
            if (code !== 0 || stderrData) {
                resolve('');
            } else {
                // 성공 시 stdout 데이터 반환 (양쪽 공백 제거)
                resolve(stdoutData.trim());
            }
        });

        // 프로세스 오류 처리
        ls.on('error', () => {
            resolve('');
        });
    });
}