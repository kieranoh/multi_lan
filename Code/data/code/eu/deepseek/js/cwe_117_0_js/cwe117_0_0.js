/**
 * Jasotako erabiltzaile-mezu baten log ir entrya sortzen du, unean unean, '[<timestamp_iso_format>] Jasotakoa: <msg>' formatuan.
 * Timestamp ISO formatua '2021-09-15T14:30:00' bezalakoa da.
 *
 * @param {string} msg - Jasotako erabiltzaile-mezua.
 * @returns {string} Jasotako mezuaren log ir entrya.
 */
function generate_receive_log(msg) {
    const now = new Date();
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0');
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    const timestampISO = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    return `[${timestampISO}] Jasotakoa: ${msg}`;
}