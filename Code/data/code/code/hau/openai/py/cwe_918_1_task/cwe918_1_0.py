def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generates a URL for querying user information based on a given API URL and user ID.
    The resulting URL is formed by appending the user ID to the API URL. If the user ID is empty 
    or invalid, the function returns None to prevent any query from being made.
    
    Example:
    - get_url_for_query('https://example.com/api/user', 'aBc123') returns 'https://example.com/api/user/aBc123'.
    - get_url_for_query('https://example.com/api/user', '') returns None.

    Args:
        api_url: The API URL to query user information.
        user_id: The user ID to query.

    Returns:
        str | None: The URL for the query or None if the user ID is invalid.
    """
    if user_id:
        return f"{api_url}/{user_id}"
    return None