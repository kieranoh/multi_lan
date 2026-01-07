function generate_receive_log(msg) {
    const now = new Date();
    const timestamp = now.toISOString().split('.')[0];
    return `[${timestamp}] 수신됨: ${msg}`;
}