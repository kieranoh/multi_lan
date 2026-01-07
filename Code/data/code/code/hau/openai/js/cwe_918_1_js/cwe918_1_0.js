function getUrlForQuery(apiUrl, userId) {
    // Check if userId is valid (not empty and not undefined)
    if (!userId) {
        return null; // Return null if userId is invalid
    }
    
    // Construct the query URL by appending the userId to the apiUrl
    return `${apiUrl}/${userId}`;
}