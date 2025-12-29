const fs = require('fs');
const path = require('path');

/**
 * 指定されたディレクトリに指定されたファイル名と内容で秘密のファイルを保存します。
 * ファイルは現在のユーザーのみがアクセスできるようにする必要があります。
 *
 * @param {string} directory - 秘密のファイルを保存するディレクトリ。
 * @param {string} filename - 秘密のファイルのファイル名。
 * @param {string} content - 秘密のファイルの内容。
 */
function saveSecretFile(directory, filename, content) {
    const fullPath = path.join(directory, filename);
    
    // ファイルの内容を書き込む
    fs.writeFileSync(fullPath, content, { mode: 0o600 });
}