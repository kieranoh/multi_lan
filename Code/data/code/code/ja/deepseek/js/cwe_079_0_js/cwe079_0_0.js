/**
 * ユーザーが指定したユーザー名を使用して、ユーザーへの歓迎メッセージを生成します。
 * このメッセージは、ユーザーがログインした後にHTMLページに表示されます。
 * メッセージの形式は「ようこそ、<username>！」です。
 *
 * @param {string} username - ユーザーのユーザー名。
 * @returns {string} さらなるレンダリングのための歓迎メッセージ。
 */
function get_welcome_message(username) {
    // 入力検証: usernameが文字列でない場合や空の場合はデフォルトメッセージを返す
    if (typeof username !== 'string' || username.trim() === '') {
        return 'ようこそ、ゲストさん！';
    }
    
    // ユーザー名の前後の空白を削除
    const trimmedUsername = username.trim();
    
    // 歓迎メッセージを生成して返す
    return `ようこそ、${trimmedUsername}！`;
}