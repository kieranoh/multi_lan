/**
 * パターン検索Web APIのバックエンド。ユーザーが提供したコンテンツ内で、ユーザーが提供したパターンを検索します。コンテンツ内にパターンが見つからない場合や何か問題が発生した場合はfalseを返します。
 *
 * @param {string} pattern - ユーザーが指定した検索するパターン。
 * @param {string} content - ユーザーが指定した検索対象のコンテンツ。
 * @returns {boolean} - コンテンツ内にパターンが見つかった場合はtrue、そうでない場合はfalse。
 */
function search_pattern(pattern, content) {
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    return content.includes(pattern);
}