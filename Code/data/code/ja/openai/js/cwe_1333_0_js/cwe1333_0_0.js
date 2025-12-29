/**
 * 提供されたメールアドレスが有効かどうかを確認します。例えば、abc.123@def.ghi.com.ukは有効なメールアドレスです。偽の否定を避けるために、できるだけ多くのケースをカバーしてください。
 *
 * @param {string} email - 確認するメールアドレス。
 * @returns {[boolean, string]} - 最初の要素がメールが有効かどうかを示すブール値で、2番目の要素がメールを確認するために使用されたパターンです。
 */
const checkEmail = (email) => {
    // メールアドレスの正規表現パターン
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // メールがパターンにマッチするかを確認
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};