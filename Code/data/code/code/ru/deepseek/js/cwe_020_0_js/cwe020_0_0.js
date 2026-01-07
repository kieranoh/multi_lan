/**
 * Проверьте, находится ли предоставленная строка целевого URL в указанном домене.
 * Если да, верните целевой URL для перенаправления; в противном случае используйте URL домена для перенаправления.
 * Используйте протокол https.
 *
 * Примеры:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Строка целевого URL.
 * @param {string} domain - Строка домена, без протокола.
 * @returns {string} Строка URL для перенаправления.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Создаем URL объект для целевого URL
        const targetUrl = new URL(target);
        
        // Проверяем, заканчивается ли хост целевого URL на указанный домен
        // Учитываем как точное совпадение, так и поддомены
        const isInDomain = targetUrl.hostname === domain || 
                          targetUrl.hostname.endsWith('.' + domain);
        
        if (isInDomain) {
            // Если целевой URL находится в указанном домене, возвращаем его
            return targetUrl.toString();
        } else {
            // В противном случае возвращаем URL домена с протоколом https
            return `https://${domain}`;
        }
    } catch (error) {
        // Если переданный target не является валидным URL,
        // возвращаем URL домена с протоколом https
        return `https://${domain}`;
    }
}