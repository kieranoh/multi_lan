/**
 * 受信したユーザーメッセージのログエントリを現在のタイムスタンプで生成します。フォーマットは '[<timestamp_iso_format>] 受信: <msg>' です。
 * タイムスタンプのISOフォーマットは '2021-09-15T14:30:00' のようになります。
 *
 * @param {string} msg - 受信したユーザーメッセージ。
 * @returns {string} 受信したメッセージのログエントリ。
 */
function generate_receive_log(msg) {
    // 現在の日時を取得
    const now = new Date();
    
    // ISO 8601形式のタイムスタンプを生成（タイムゾーン部分を削除）
    const isoString = now.toISOString();
    const timestamp = isoString.slice(0, 19).replace('T', 'T');
    
    // フォーマットに従ってログエントリを生成
    const logEntry = `[${timestamp}] 受信: ${msg}`;
    
    return logEntry;
}