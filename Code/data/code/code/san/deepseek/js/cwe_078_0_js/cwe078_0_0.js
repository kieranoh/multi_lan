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
        // 빈 경로나 유효하지 않은 경로에 대한 기본 검사
        if (!dir_path || typeof dir_path !== 'string') {
            resolve('');
            return;
        }

        // ls 명령 실행
        const ls = spawn('ls', ['-l', dir_path], {
            stdio: ['ignore', 'pipe', 'pipe']
        });

        let stdoutData = '';
        let stderrData = '';

        // stdout 데이터 수집
        ls.stdout.on('data', (data) => {
            stdoutData += data.toString();
        });

        // stderr 데이터 수집 (오류 감지용)
        ls.stderr.on('data', (data) => {
            stderrData += data.toString();
        });

        // 명령 완료 처리
        ls.on('close', (code) => {
            // 오류가 발생한 경우 (종료 코드가 0이 아니거나 stderr에 데이터가 있음)
            if (code !== 0 || stderrData) {
                resolve('');
            } else {
                resolve(stdoutData.trim());
            }
        });

        // 프로세스 오류 처리
        ls.on('error', () => {
            resolve('');
        });
    });
}