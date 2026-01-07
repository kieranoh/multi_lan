package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	var tarReader *tar.Reader

	// Check if it's a gzipped tar file
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

		// Construct the full path for the file
		targetPath := filepath.Join(destPath, header.Name)

		// Check for directory traversal attacks
		if !isSafePath(destPath, targetPath) {
			return false
		}

		// Handle different types of entries
		switch header.Typeflag {
		case tar.TypeDir:
			// Create directory
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Create file
			if err := extractFile(tarReader, targetPath, header); err != nil {
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
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// Skip unsupported types
			continue
		}
	}

	return true
}

// extractFile extracts a single file from tar reader
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
	// Create parent directories if needed
	if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
		return err
	}

	// Create the file
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// Copy file contents
	if _, err := io.CopyN(file, tarReader, header.Size); err != nil && err != io.EOF {
		return err
	}

	return nil
}

// isSafePath checks if the target path is within the destination directory
func isSafePath(basePath, targetPath string) bool {
	rel, err := filepath.Rel(basePath, targetPath)
	if err != nil {
		return false
	}
	
	// Check if the relative path tries to go outside the base directory
	if rel == ".." || len(rel) >= 3 && rel[0:3] == "../" {
		return false
	}
	
	return true
}