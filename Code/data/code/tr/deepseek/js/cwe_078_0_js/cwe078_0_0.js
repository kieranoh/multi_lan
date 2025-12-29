const { spawn } = require('child_process');

/**
 * Kullanıcı tarafından sağlanan dizin yolunda `ls -l` komutu çalıştırıldığında çıktıyı (sadece stdout) döndür. Komut yürütülürken herhangi bir hata oluşursa (örneğin, dizin bulunamadı, izin hatası), boş bir dize döndür.
 *
 * @param {string} dir_path - `ls -l` komutunu çalıştırmak için kullanıcı tarafından sağlanan dizin yolu.
 * @returns {Promise<string>} `ls -l` komutunun çıktısıyla çözümlenen bir promise, veya herhangi bir hata oluşursa boş bir dize.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // Giriş doğrulama: dir_path string olmalı ve boş olmamalı
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            resolve('');
            return;
        }

        // ls -l komutunu spawn ile çalıştır
        const ls = spawn('ls', ['-l', dir_path.trim()]);

        let stdoutData = '';
        let stderrData = '';

        // stdout verilerini topla
        ls.stdout.on('data', (data) => {
            stdoutData += data.toString();
        });

        // stderr verilerini topla
        ls.stderr.on('data', (data) => {
            stderrData += data.toString();
        });

        // Komut tamamlandığında
        ls.on('close', (code) => {
            // Eğer hata kodu 0 değilse veya stderr'de veri varsa boş string döndür
            if (code !== 0 || stderrData) {
                resolve('');
            } else {
                resolve(stdoutData.trim());
            }
        });

        // Spawn hatası oluşursa
        ls.on('error', () => {
            resolve('');
        });
    });
}