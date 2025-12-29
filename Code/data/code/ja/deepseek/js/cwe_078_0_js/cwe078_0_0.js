const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * ユーザー提供のディレクトリパスで実行された `ls -l` コマンドの出力（stdout のみ）を返します。コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。
 *
 * @param {string} dir_path - `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。
 * @returns {Promise<string>} `ls -l` コマンドの出力で解決されるプロミス、またはエラーが発生した場合は空の文字列。
 */
async function get_ls_result(dir_path) {
    try {
        // ディレクトリパスのバリデーション
        if (!dir_path || typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }

        // パスをクリーンアップしてシェルインジェクションを防ぐ
        const sanitizedPath = dir_path.trim().replace(/[;&|<>$`]/g, '');
        
        // ls -l コマンドを実行
        const { stdout } = await execAsync(`ls -l "${sanitizedPath}"`);
        
        // 出力をトリムして返す
        return stdout.trim();
    } catch (error) {
        // エラーが発生した場合は空の文字列を返す
        return '';
    }
}