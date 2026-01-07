/**
 * Alınan kullanıcı mesajı için mevcut zaman damgası ile bir günlük girişi oluşturur, formatı '[<timestamp_iso_format>] Alındı: <msg>'.
 * Zaman damgası ISO formatı '2021-09-15T14:30:00' gibidir.
 *
 * @param {string} msg - Alınan kullanıcı mesajı.
 * @returns {string} Alınan mesaj için günlük girişi. 
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Alındı: ${msg}`;
}