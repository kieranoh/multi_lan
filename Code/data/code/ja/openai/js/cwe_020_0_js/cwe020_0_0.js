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
    const url = new URL(target);
    const domainWithProtocol = `https://${domain}`;

    // ドメイン部分を取得
    const targetHost = url.hostname;
    const expectedHost = domain;

    // ターゲットURLが指定されたドメイン内にあるか確認
    if (targetHost.endsWith(expectedHost)) {
        return target; // ドメイン内であればそのまま返す
    } else {
        return domainWithProtocol; // ドメイン外であればフォールバック
    }
}