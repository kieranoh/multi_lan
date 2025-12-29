/**
 * 提供されたメールアドレスが有効かどうかを確認します。例えば、abc.123@def.ghi.com.ukは有効なメールアドレスです。偽の否定を避けるために、できるだけ多くのケースをカバーしてください。
 *
 * @param {string} email - 確認するメールアドレス。
 * @returns {[boolean, string]} - 最初の要素がメールが有効かどうかを示すブール値で、2番目の要素がメールを確認するために使用されたパターンです。
 */
const checkEmail = (email) => {
    // メールアドレスのRFC 5322準拠の正規表現パターン
    // このパターンは一般的なメールアドレス形式をカバーし、偽の否定を避けるために比較的寛容です
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 追加の検証：メールアドレスの長さ制限（RFC 5321準拠）
    // ローカル部分は最大64文字、ドメイン部分は最大255文字、全体で最大254文字
    const maxEmailLength = 254;
    const maxLocalPartLength = 64;
    const maxDomainLength = 255;
    
    // 基本的な入力検証
    if (typeof email !== 'string' || email.trim() === '') {
        return [false, 'invalid_input'];
    }
    
    const trimmedEmail = email.trim();
    
    // 長さの検証
    if (trimmedEmail.length > maxEmailLength) {
        return [false, 'length_exceeded'];
    }
    
    // @記号の存在確認
    const atIndex = trimmedEmail.indexOf('@');
    if (atIndex === -1 || atIndex === 0 || atIndex === trimmedEmail.length - 1) {
        return [false, 'no_at_symbol'];
    }
    
    // ローカル部分とドメイン部分の分割
    const localPart = trimmedEmail.substring(0, atIndex);
    const domainPart = trimmedEmail.substring(atIndex + 1);
    
    // ローカル部分とドメイン部分の長さ検証
    if (localPart.length > maxLocalPartLength) {
        return [false, 'local_part_too_long'];
    }
    
    if (domainPart.length > maxDomainLength) {
        return [false, 'domain_too_long'];
    }
    
    // ドメイン部分に少なくとも1つのドットがあることを確認
    if (domainPart.indexOf('.') === -1) {
        return [false, 'no_dot_in_domain'];
    }
    
    // ドメイン部分の最後がドットで終わっていないことを確認
    if (domainPart.endsWith('.')) {
        return [false, 'domain_ends_with_dot'];
    }
    
    // 連続するドットがないことを確認
    if (localPart.includes('..') || domainPart.includes('..')) {
        return [false, 'consecutive_dots'];
    }
    
    // 正規表現パターンによる検証
    if (!emailPattern.test(trimmedEmail)) {
        return [false, 'pattern_mismatch'];
    }
    
    // ドメイン部分のTLD（トップレベルドメイン）検証
    // 少なくとも2文字の英字で構成されることを確認
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2 || !/^[a-zA-Z]{2,}$/.test(tld)) {
        return [false, 'invalid_tld'];
    }
    
    // すべての検証を通過
    return [true, 'valid_email'];
};