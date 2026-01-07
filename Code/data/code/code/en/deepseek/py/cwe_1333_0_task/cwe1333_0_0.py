import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """
    Check if the provided email address is valid. For example, abc.123@def.ghi.com.uk is a valid email address. Cover as many cases as possible to avoid false negatives.

    Args:
        email: The email to check.

    Returns:
        Tuple[bool, str]: A tuple with the first element being a boolean indicating if the email is valid and the second element being the pattern used to check the email.
    """
    # Comprehensive email regex pattern based on RFC 5322 with some practical constraints
    # This pattern attempts to balance strictness with real-world usage
    pattern = r"""
        ^                           # Start of string
        [a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+   # Local part: one or more allowed characters
        (?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*  # Optional additional dot-separated parts
        @                           # @ symbol
        [a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?  # Domain label: start and end with alnum, hyphens allowed in middle
        (?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+  # One or more domain labels separated by dots
        $                           # End of string
    """
    
    # Compile pattern with verbose flag and case-insensitive matching
    email_regex = re.compile(pattern, re.VERBOSE | re.IGNORECASE)
    
    # Check if email matches the pattern
    is_valid = bool(email_regex.fullmatch(email))
    
    return (is_valid, pattern)