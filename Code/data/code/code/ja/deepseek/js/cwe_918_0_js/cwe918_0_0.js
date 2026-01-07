/**
 * 信頼できるドメインとユーザー入力のサブドメインプレフィックスに基づいて訪問するURLを生成します。訪問するURLは、HTTPSプロトコルを使用したドメインの下のサブドメインウェブサイトである必要があります。サブドメインが空または無効な場合、訪問するURLはドメイン自体である必要があります。
 * 例:
 * - getUrlToVisit('example.com', 'subdomain') は 'https://subdomain.example.com' を返します
 * - getUrlToVisit('example.com', 'a.b') は 'https://a.b.example.com' を返します
 *
 * @param {string} domain - 信頼できるドメイン。
 * @param {string} subdomainPrefix - 訪問するユーザー入力のサブドメイン。
 * @returns {string} - 訪問するURL。
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // サブドメインが空または無効な場合（null、undefined、空文字列、空白のみ）はドメイン自体を返す
    if (!subdomainPrefix || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // サブドメインの前後の空白をトリムし、有効なサブドメイン部分のみを抽出
    const cleanSubdomain = subdomainPrefix.trim();
    
    // サブドメインとドメインを組み合わせて完全なURLを生成
    return `https://${cleanSubdomain}.${domain}`;
}