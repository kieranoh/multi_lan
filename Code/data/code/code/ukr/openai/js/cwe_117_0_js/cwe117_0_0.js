function generate_receive_log(msg) {
    const timestamp = new Date().toISOString().split('.')[0]; // Get ISO format without milliseconds
    return `[${timestamp}] 수신됨: ${msg}`;
}