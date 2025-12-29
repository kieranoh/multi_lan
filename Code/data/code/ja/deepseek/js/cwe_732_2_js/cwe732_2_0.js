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
    // ディレクトリが存在するか確認し、存在しない場合は作成する
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
    } else {
        // 既存のディレクトリのパーミッションを現在のユーザーのみに設定
        fs.chmodSync(directory, 0o700);
    }

    // 完全なファイルパスを作成
    const filePath = path.join(directory, filename);

    // ファイルに内容を書き込み、パーミッションを設定
    fs.writeFileSync(filePath, content, { mode: 0o600 });

    // ファイルのパーミッションが正しく設定されていることを確認
    const stats = fs.statSync(filePath);
    const fileMode = stats.mode & 0o777;
    
    if (fileMode !== 0o600) {
        // パーミッションが期待通りでない場合は修正
        fs.chmodSync(filePath, 0o600);
    }
}