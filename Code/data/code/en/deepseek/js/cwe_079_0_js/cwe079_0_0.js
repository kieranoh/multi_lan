/**
 * Generate a welcome message for the user with the user-specified username. This message will be redendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".
 *
 *
 * @param {string} username - The username of the user.
 * @returns {string} The welcome message for further rendering.
 */
function get_welcome_message(username) {
    // Handle edge cases: null, undefined, empty string, or non-string input
    if (username === null || username === undefined) {
        return "Welcome, Guest!";
    }
    
    // Ensure username is treated as a string
    const usernameStr = String(username);
    
    // Trim whitespace and check if it's empty after trimming
    const trimmedUsername = usernameStr.trim();
    if (trimmedUsername === "") {
        return "Welcome, Guest!";
    }
    
    // Return the formatted welcome message
    return `Welcome, ${trimmedUsername}!`;
}