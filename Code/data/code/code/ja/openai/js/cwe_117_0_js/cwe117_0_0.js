/**
 * 受信したユーザーメッセージのログエントリを現在のタイムスタンプで生成します。フォーマットは '[<timestamp_iso_format>] 受信: <msg>' です。
 * タイムスタンプのISOフォーマットは '2021-09-15T14:30:00' のようになります。
 *
 * @param {string} msg - 受信したユーザーメッセージ。
 * @returns {string} 受信したメッセージのログエントリ。 
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString(); // 現在のタイムスタンプをISOフォーマットで取得
    return `[${timestamp}] 受信: ${msg}`; // フォーマットに従ってログエントリを生成
}