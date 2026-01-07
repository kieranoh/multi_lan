const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    // Ensure the directory exists
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // Define the full path for the secret file
    const filePath = path.join(directory, filename);

    // Write the content to the file
    fs.writeFileSync(filePath, content);

    // Set the permissions so that only the current user can access the file
    const currentUser = os.userInfo().username;
    const command = `chmod 600 ${filePath}`;
    
    // Execute the command to change file permissions
    require('child_process').execSync(command);

    console.log(`Secret file saved at: ${filePath}`);
}