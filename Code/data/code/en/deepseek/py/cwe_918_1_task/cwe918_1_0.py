from typing import Optional

def get_url_for_query(api_url: str, user_id: str) -> Optional[str]:
    """
    Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return None so that no query will be made.
    Examples:
    - get_url_for_query('https://example.com/api/user', 'aBc123') returns 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') returns None

    Args:
        api_url: The API URL to query user info.
        user_id: The user ID to query.

    Returns:
        str | None: The URL for query.
    """
    # Check if user_id is empty or invalid
    if not user_id or not user_id.strip():
        return None
    
    # Ensure api_url doesn't end with a slash to avoid double slashes
    api_url = api_url.rstrip('/')
    
    # Construct the query URL
    query_url = f"{api_url}/{user_id}"
    
    return query_url