const fs = require('fs');
const path = require('path');
const os = require('os');
const process = require('process');

/**
 * Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin.
 * Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.
 *
 * @param {string} directory - Gizli dosyanın kaydedileceği dizin.
 * @param {string} filename - Gizli dosyanın dosya adı.
 * @param {string} content - Gizli dosyanın içeriği.
 */
function saveSecretFile(directory, filename, content) {
    // Dizin varsa kontrol et, yoksa oluştur
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    const filePath = path.join(directory, filename);

    // Dosyayı yaz
    fs.writeFileSync(filePath, content);

    // Dosyanın izinlerini yalnızca mevcut kullanıcıya erişilebilir olacak şekilde ayarla
    const uid = process.getuid(); // Mevcut kullanıcı ID'sini al
    fs.chmodSync(filePath, 0o600); // Sadece kullanıcıya okuma ve yazma izni ver
}