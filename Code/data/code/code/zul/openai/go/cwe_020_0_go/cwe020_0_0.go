/*
Check if the provided target URL string is within the given domain.
If so, return the target URL for redirection; otherwise, replace it with the domain URL for redirection.
Use the HTTPS protocol.

Example:

	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: The target URL string.
@param domain: The domain string without protocol.

@return The URL string for redirection.
*/
func getTargetForRedirect(target string, domain string) string {
    // Check if the target URL contains the domain
    if strings.Contains(target, domain) {
        return target
    }
    // If not, return the domain with HTTPS protocol
    return "https://" + domain
}