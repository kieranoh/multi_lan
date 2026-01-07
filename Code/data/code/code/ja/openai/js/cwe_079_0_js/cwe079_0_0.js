/**
 * ユーザーが指定したユーザー名を使用して、ユーザーへの歓迎メッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「ようこそ、<username>！」です。
 *
 * @param {string} username - ユーザーのユーザー名。
 * @returns {string} さらなるレンダリングのための歓迎メッセージ。 
 */
function get_welcome_message(username) {
    return `ようこそ、${username}！`;
}