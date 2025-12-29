package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/* दी गई गंतव्य पथ पर tar फ़ाइल की सामग्री निकालें।
यदि निकासी सफल होती है, तो true लौटाएं; अन्यथा, यदि निकासी प्रक्रिया के दौरान कोई त्रुटि होती है (जैसे फ़ाइल नहीं मिली, अनुमति त्रुटि, सभी सामग्री निकालने में असमर्थ), तो बस false लौटाएं।

@param tarPath: tar फ़ाइल का पथ
@param destPath: गंतव्य फ़ोल्डर का पथ

@return यदि निकासी सफल होती है तो true; अन्यथा, false */
func extractTarToPath(tarPath string, destPath string) bool {
	// 1. tar फ़ाइल खोलें
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// 2. gzip डिकम्प्रेशन के लिए चेक करें (वैकल्पिक)
	var tarReader io.Reader = file
	if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = gzReader
	}

	// 3. tar रीडर बनाएं
	tr := tar.NewReader(tarReader)

	// 4. प्रत्येक फ़ाइल/फ़ोल्डर के लिए निकालें
	for {
		header, err := tr.Next()
		if err == io.EOF {
			break // tar फ़ाइल का अंत
		}
		if err != nil {
			return false
		}

		// सुरक्षा जांच: फ़ाइल पथ को गंतव्य पथ के भीतर ही रखें
		targetPath := filepath.Join(destPath, header.Name)
		if !isWithinDest(destPath, targetPath) {
			return false
		}

		// फ़ाइल प्रकार के अनुसार प्रक्रिया करें
		switch header.Typeflag {
		case tar.TypeDir:
			// फ़ोल्डर बनाएं
			if err := os.MkdirAll(targetPath, 0755); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// नियमित फ़ाइल बनाएं
			if err := extractFile(tr, targetPath, header.FileInfo().Mode()); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// सिमलिंक बनाएं
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// हार्ड लिंक बनाएं
			linkPath := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// अन्य फ़ाइल प्रकारों को अनदेखा करें (उपकरण, फ़ाइफो, आदि)
			continue
		}
	}

	return true
}

// extractFile tar रीडर से फ़ाइल सामग्री निकालकर निर्दिष्ट पथ पर लिखता है
func extractFile(tr *tar.Reader, targetPath string, mode os.FileMode) error {
	// फ़ाइल बनाने से पहले फ़ोल्डर सुनिश्चित करें
	dir := filepath.Dir(targetPath)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return err
	}

	// फ़ाइल बनाएं
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, mode)
	if err != nil {
		return err
	}
	defer file.Close()

	// फ़ाइल सामग्री कॉपी करें
	if _, err := io.Copy(file, tr); err != nil {
		return err
	}

	return nil
}

// isWithinDest जांचता है कि लक्ष्य पथ गंतव्य पथ के भीतर है (पथ ट्रैवर्सल हमलों से बचाव)
func isWithinDest(destPath, targetPath string) bool {
	rel, err := filepath.Rel(destPath, targetPath)
	if err != nil {
		return false
	}
	return rel != ".." && !filepath.IsAbs(rel) && rel[:2] != ".."
}