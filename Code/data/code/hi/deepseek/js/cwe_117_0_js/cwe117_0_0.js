/**
 * प्राप्त उपयोगकर्ता संदेश के लिए वर्तमान समय के साथ एक लॉग प्रविष्टि उत्पन्न करता है, प्रारूप में '[<timestamp_iso_format>] प्राप्त: <msg>'.
 * टाइमस्टैम्प ISO प्रारूप '2021-09-15T14:30:00' जैसा होता है।
 *
 * @param {string} msg - प्राप्त उपयोगकर्ता संदेश।
 * @returns {string} प्राप्त संदेश के लिए लॉग प्रविष्टि।
 */
function generate_receive_log(msg) {
    // वर्तमान तिथि और समय प्राप्त करें
    const now = new Date();
    
    // ISO प्रारूप में टाइमस्टैम्प बनाएं (YYYY-MM-DDTHH:MM:SS)
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0'); // महीना 0-आधारित है
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    // आवश्यक ISO प्रारूप में टाइमस्टैम्प बनाएं
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // लॉग प्रविष्टि बनाएं और लौटाएं
    return `[${timestamp}] प्राप्त: ${msg}`;
}