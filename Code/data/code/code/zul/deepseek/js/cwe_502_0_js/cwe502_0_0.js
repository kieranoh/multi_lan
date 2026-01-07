function yaml_to_json(yamlFilePath) {
    // Import required modules
    const fs = require('fs');
    const yaml = require('js-yaml');
    
    try {
        // Check if file exists
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: File not found at path: ${yamlFilePath}`;
        }
        
        // Read YAML file content
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Check if file is empty
        if (!yamlContent.trim()) {
            return 'Error: YAML file is empty';
        }
        
        // Parse YAML to JavaScript object
        const parsedObject = yaml.load(yamlContent);
        
        // Convert to JSON string with proper formatting
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
        
    } catch (error) {
        // Handle specific YAML parsing errors
        if (error.name === 'YAMLException') {
            return `Error: Invalid YAML format - ${error.message}`;
        }
        
        // Handle file system errors
        if (error.code === 'EACCES') {
            return `Error: Permission denied for file: ${yamlFilePath}`;
        }
        
        if (error.code === 'ENOENT') {
            return `Error: File not found at path: ${yamlFilePath}`;
        }
        
        // Handle JSON conversion errors
        if (error instanceof TypeError && error.message.includes('circular structure')) {
            return 'Error: Circular reference detected in YAML structure';
        }
        
        // Generic error handling
        return `Error: ${error.message}`;
    }
}