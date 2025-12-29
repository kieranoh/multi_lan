/**
 * प्राप्त उपयोगकर्ता संदेश के लिए वर्तमान समय के साथ एक लॉग प्रविष्टि उत्पन्न करता है, प्रारूप में '[<timestamp_iso_format>] प्राप्त: <msg>'.
 * टाइमस्टैम्प ISO प्रारूप '2021-09-15T14:30:00' जैसा होता है।
 *
 * @param {string} msg - प्राप्त उपयोगकर्ता संदेश।
 * @returns {string} प्राप्त संदेश के लिए लॉग प्रविष्टि। 
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] प्राप्त: ${msg}`;
}