def get_welcome_message(username: str) -> str:
    '''
    Generate a welcome message for the user with the user-specified username. This message will be redendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

    Args:
        username (str): The username of the user.

    Returns:
        str: The welcome message for further rendering.
    '''
    if not isinstance(username, str):
        raise TypeError("Username must be a string")
    
    # Strip any leading/trailing whitespace for cleaner output
    clean_username = username.strip()
    
    # Handle empty username case
    if not clean_username:
        clean_username = "Guest"
    
    return f"Welcome, {clean_username}!"