import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/**
Extract the content of the tar file to the given destination path.
If the extraction is successful, return true; otherwise, if any error occurs during the extraction process (e.g. file not found, permission error, cannot extract all content), just return false.

@param tarPath: the path to the tar file
@param destPath: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Determine if the file is gzipped by checking the extension
	// or by attempting to create a gzip reader
	var tarReader *tar.Reader
	if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Create destination directory if it doesn't exist
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Extract each file from the tar archive
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false
		}

		// Construct the full path for the file/directory
		targetPath := filepath.Join(destPath, header.Name)

		// Check for path traversal attempts
		if !isSafePath(destPath, targetPath) {
			return false
		}

		// Handle the entry based on its type
		switch header.Typeflag {
		case tar.TypeDir:
			// Create directory
			if err := os.MkdirAll(targetPath, 0755); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Create file
			if err := extractFile(tarReader, targetPath, header.Mode); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// Create symbolic link
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Create hard link
			linkPath := filepath.Join(destPath, header.Linkname)
			if !isSafePath(destPath, linkPath) {
				return false
			}
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// Skip unsupported types (e.g., character/block devices, FIFOs)
			continue
		}
	}

	return true
}

// extractFile writes the contents of a tar entry to a file
func extractFile(src io.Reader, destPath string, mode int64) error {
	// Ensure the parent directory exists
	if err := os.MkdirAll(filepath.Dir(destPath), 0755); err != nil {
		return err
	}

	// Create the file
	file, err := os.OpenFile(destPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// Copy the contents
	_, err = io.Copy(file, src)
	return err
}

// isSafePath checks if the target path is within the destination directory
// to prevent path traversal attacks
func isSafePath(basePath, targetPath string) bool {
	relPath, err := filepath.Rel(basePath, targetPath)
	if err != nil {
		return false
	}
	// Check if the relative path starts with ".." or is absolute
	return relPath != ".." && !filepath.IsAbs(relPath) && relPath[:2] != ".."
}