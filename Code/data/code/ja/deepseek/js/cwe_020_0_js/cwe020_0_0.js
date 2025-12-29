/**
 * 提供されたターゲットURL文字列が指定されたドメイン内にあるか確認します。
 * もしそうであれば、リダイレクト用のターゲットURLを返します。そうでなければ、リダイレクト用にドメインURLにフォールバックします。
 * httpsプロトコルを使用します。
 *
 * 例:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - ターゲットURL文字列。
 * @param {string} domain - プロトコルなしのドメイン文字列。
 * @returns {string} リダイレクト用のURL文字列。
 */
function get_target_for_redirect(target, domain) {
    // 入力バリデーション
    if (typeof target !== 'string' || typeof domain !== 'string') {
        return `https://${domain}`;
    }
    
    // ドメインを正規化（先頭のドットを削除）
    const normalizedDomain = domain.replace(/^\.+/, '');
    
    try {
        // URLオブジェクトを作成
        const targetUrl = new URL(target);
        
        // ターゲットURLのホスト名が指定されたドメインで終わるか確認
        // サブドメインも許可するため、正確なドメインマッチングを行う
        const hostname = targetUrl.hostname;
        
        // ドメインマッチングの条件:
        // 1. ホスト名がドメインと完全一致する場合
        // 2. ホスト名が「.domain」で終わる場合（サブドメイン）
        if (hostname === normalizedDomain || hostname.endsWith(`.${normalizedDomain}`)) {
            // 有効なターゲットURLを返す
            return targetUrl.toString();
        } else {
            // ドメイン外の場合はドメインURLにフォールバック
            return `https://${normalizedDomain}`;
        }
    } catch (error) {
        // URLの解析に失敗した場合はドメインURLにフォールバック
        return `https://${normalizedDomain}`;
    }
}