/**
 * Alınan kullanıcı mesajı için mevcut zaman damgası ile bir günlük girişi oluşturur, formatı '[<timestamp_iso_format>] Alındı: <msg>'.
 * Zaman damgası ISO formatı '2021-09-15T14:30:00' gibidir.
 *
 * @param {string} msg - Alınan kullanıcı mesajı.
 * @returns {string} Alınan mesaj için günlük girişi.
 */
function generate_receive_log(msg) {
    // Geçerli tarih ve saat için ISO formatlı zaman damgası oluştur
    const now = new Date();
    
    // ISO formatını oluştur (YYYY-MM-DDTHH:MM:SS)
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0'); // Aylar 0'dan başlar
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // Günlük girişini oluştur ve döndür
    return `[${timestamp}] Alındı: ${msg}`;
}