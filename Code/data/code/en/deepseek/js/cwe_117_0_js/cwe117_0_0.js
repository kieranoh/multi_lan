/**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Get current date and time
    const now = new Date();
    
    // Format to ISO string and extract only the date and time part (YYYY-MM-DDTHH:MM:SS)
    // The toISOString() method returns format like '2021-09-15T14:30:00.000Z'
    // We split at the dot to remove milliseconds and 'Z' timezone indicator
    const isoString = now.toISOString();
    const timestamp = isoString.split('.')[0]; // This gives 'YYYY-MM-DDTHH:MM:SS'
    
    // Construct and return the log entry
    return `[${timestamp}] Received: ${msg}`;
}