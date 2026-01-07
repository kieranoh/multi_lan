const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * 사용자가 제공한 디렉토리 경로에서 실행될 때 `ls -l` 명령의 출력(오직 stdout)을 반환합니다.
 * 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 * 
 * @param {string} dir_path - `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.
 * @returns {Promise<string>} `ls -l` 명령의 출력으로 해결되는 프로미스, 또는 오류가 발생하면 빈 문자열입니다.
 */
async function get_ls_result(dir_path) {
    try {
        // 경로에 공백이나 특수 문자가 있을 경우를 대비하여 따옴표로 감싸기
        const sanitizedPath = `"${dir_path.replace(/"/g, '\\"')}"`;
        const { stdout } = await execAsync(`ls -l ${sanitizedPath}`);
        return stdout;
    } catch (error) {
        // 모든 종류의 오류에 대해 빈 문자열 반환
        return '';
    }
}