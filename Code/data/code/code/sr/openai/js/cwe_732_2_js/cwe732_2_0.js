const fs = require('fs');
const path = require('path');
const os = require('os');
const { promisify } = require('util');

const mkdir = promisify(fs.mkdir);
const writeFile = promisify(fs.writeFile);
const chmod = promisify(fs.chmod);

async function saveSecretFile(directory, filename, content) {
    const userHomeDir = os.homedir();
    const fullDirectory = path.join(userHomeDir, directory);
    const fullPath = path.join(fullDirectory, filename);

    try {
        // Kreiraj direktorijum ako ne postoji
        await mkdir(fullDirectory, { recursive: true });

        // Upisivanje sadržaja u tajni fajl
        await writeFile(fullPath, content);

        // Postavljanje prava pristupa na fajl (samo za trenutnog korisnika)
        await chmod(fullPath, 0o600); // vlasnik može čitati i pisati, ostali nemaju pristup
    } catch (error) {
        console.error(`Greška prilikom čuvanja tajnog fajla: ${error.message}`);
    }
}