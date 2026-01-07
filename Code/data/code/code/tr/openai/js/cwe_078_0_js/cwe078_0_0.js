/**
 * Kullanıcı tarafından sağlanan dizin yolunda `ls -l` komutu çalıştırıldığında çıktıyı (sadece stdout) döndürür. 
 * Komut yürütülürken herhangi bir hata oluşursa (örneğin, dizin bulunamadı, izin hatası), boş bir dize döner.
 *
 * @param {string} dir_path - `ls -l` komutunu çalıştırmak için kullanıcı tarafından sağlanan dizin yolu.
 * @returns {Promise<string>} `ls -l` komutunun çıktısıyla çözümlenen bir promise, veya herhangi bir hata oluşursa boş bir dize.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        const { exec } = require('child_process');

        exec(`ls -l "${dir_path}"`, (error, stdout) => {
            if (error) {
                resolve(''); // Hata durumunda boş bir dize döner
            } else {
                resolve(stdout.trim()); // Çıktıyı döner
            }
        });
    });
}