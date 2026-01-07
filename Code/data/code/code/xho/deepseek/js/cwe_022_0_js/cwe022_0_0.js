const fs = require('fs');
const path = require('path');

function read_file_from_dir(filename, dir_path) {
    try {
        // Construct the full file path
        const filePath = path.join(dir_path, filename);
        
        // Read file synchronously with UTF-8 encoding
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // Return empty string for any error (file not found, permission error, etc.)
        return '';
    }
}