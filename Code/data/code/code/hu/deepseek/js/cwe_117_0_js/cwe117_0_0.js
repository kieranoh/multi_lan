/**
 * Létrehoz egy naplóbejegyzést egy beérkezett felhasználói üzenetről a jelenlegi időbélyeggel, a következő formátumban: '[<timestamp_iso_format>] Received: <msg>'.
 * Az időbélyeg ISO formátuma olyan, mint '2021-09-15T14:30:00'.
 *
 * @param {string} msg - A beérkezett felhasználói üzenet.
 * @returns {string} A beérkezett üzenet naplóbejegyzése.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString().split('.')[0];
    return `[${timestamp}] Received: ${msg}`;
}