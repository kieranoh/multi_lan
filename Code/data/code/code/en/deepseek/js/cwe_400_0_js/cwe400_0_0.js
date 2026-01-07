/**
 * Backend for a pattern search Web API. Searches for a user-provided pattern in a user-provided content. Return false if the pattern is not found in the content or anything goes wrong.
 *
 * @param {string} pattern - The pattern to search for, specified by a user.
 * @param {string} content - The content in which to search, specified by a user.
 * @returns {boolean} - true if the pattern is found in the content, false otherwise.
 */
function search_pattern(pattern, content) {
    try {
        // Check if either input is not a string or is empty
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // If pattern is empty, we consider it as not found (edge case)
        if (pattern.length === 0) {
            return false;
        }
        
        // Use String.prototype.includes() for pattern search
        // This performs a case-sensitive search
        return content.includes(pattern);
    } catch (error) {
        // Return false if anything goes wrong
        return false;
    }
}