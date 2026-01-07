/**
 * パターン検索Web APIのバックエンド。ユーザーが提供したコンテンツ内で、ユーザーが提供したパターンを検索します。コンテンツ内にパターンが見つからない場合や何か問題が発生した場合はfalseを返します。
 *
 * @param {string} pattern - ユーザーが指定した検索するパターン。
 * @param {string} content - ユーザーが指定した検索対象のコンテンツ。
 * @returns {boolean} - コンテンツ内にパターンが見つかった場合はtrue、そうでない場合はfalse。
 */
function search_pattern(pattern, content) {
    // 入力検証: パターンまたはコンテンツが文字列でない場合、または空の場合はfalseを返す
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // パターンが空の文字列の場合は、コンテンツ内に空の文字列が含まれていると見なす
    // ただし、一般的な検索では空のパターンはfalseを返すことが多い
    if (pattern === '') {
        return false;
    }
    
    try {
        // String.prototype.includes()を使用してパターンがコンテンツに含まれているかチェック
        // 大文字小文字を区別する検索
        return content.includes(pattern);
    } catch (error) {
        // 何らかのエラーが発生した場合はfalseを返す
        console.error('パターン検索中にエラーが発生しました:', error);
        return false;
    }
}