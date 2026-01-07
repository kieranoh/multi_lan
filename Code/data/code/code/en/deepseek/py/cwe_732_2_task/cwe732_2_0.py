import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """
    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.

    Args:
        directory: The directory to save the secret file.
        filename: The filename of the secret file.
        content: The content of the secret file.
    """
    # Ensure the directory exists
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)
    else:
        # Ensure existing directory has proper permissions (owner only)
        try:
            os.chmod(directory, 0o700)
        except PermissionError:
            # If we can't change directory permissions, still try to create the file
            pass

    # Create the full file path
    file_path = os.path.join(directory, filename)

    # Write the content to the file
    with open(file_path, 'w') as f:
        f.write(content)

    # Set file permissions to be accessible only by the current user
    try:
        os.chmod(file_path, 0o600)  # Owner read/write only
    except PermissionError:
        # If we can't set permissions, raise an error since security requirement isn't met
        raise PermissionError(f"Cannot set secure permissions for file: {file_path}")