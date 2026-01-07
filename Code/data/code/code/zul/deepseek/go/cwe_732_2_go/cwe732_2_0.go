import (
    "os"
    "path/filepath"
    "io/ioutil"
)

// saveSecreteFile saves a secret file with the given filename and content in the specified directory.
// The file is only accessible by the current user (permissions: 0600).
//
// @param directory The directory where the secret file will be saved.
// @param filename The name of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) error {
    // Ensure the directory exists
    if err := os.MkdirAll(directory, 0700); err != nil {
        return err
    }

    // Construct the full file path
    filePath := filepath.Join(directory, filename)

    // Write content to file with read/write permissions for owner only (0600)
    if err := ioutil.WriteFile(filePath, []byte(content), 0600); err != nil {
        return err
    }

    return nil
}