from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Stores the provided information in an existing HTTP response header dictionary based on the specified type.
    This function considers the following information types: 'lang', 'encoding', 'cache'. 
    These are stored under the 'Accept-Language', 'Accept-Encoding', and 'Cache-Control' keys respectively.
    If the specified information type is valid, it should be included in the updated response header.
    In case of an issue, the function returns the original header dictionary unchanged.

    Args:
        info_type (str): The type of information to store in the header.
        info_content (str): The content of the information to store in the header.
        header (Dict[str, str]): The existing response header dictionary.

    Returns:
        Dict[str, str]: The updated response header dictionary containing the stored information.'''

    # Define a mapping of info_type to the corresponding header key
    header_mapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }

    # Check if the provided info_type is valid
    if info_type in header_mapping:
        # Update the header with the corresponding key and content
        header[header_mapping[info_type]] = info_content

    # Return the updated header
    return header