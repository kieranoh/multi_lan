/**
 * Сгенерировать URL для посещения на основе доверенного домена и префикса поддомена, введенного пользователем.
 * Ожидаемый URL для посещения должен быть сайтом поддомена под доменом с протоколом HTTPS.
 * Если поддомен пустой или недействительный, URL для посещения должен быть сам домен.
 * 
 * @param {string} domain - Доверенный домен.
 * @param {string} subdomainPrefix - Поддомен, который нужно посетить, введенный пользователем.
 * @returns {string} - URL для посещения.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Удаляем начальные и конечные пробелы
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Проверяем, является ли поддомен пустым или недействительным
    if (!trimmedSubdomain || trimmedSubdomain === '' || trimmedSubdomain === '.') {
        return `https://${trimmedDomain}`;
    }
    
    // Удаляем точку в конце поддомена, если она есть
    let cleanSubdomain = trimmedSubdomain;
    if (cleanSubdomain.endsWith('.')) {
        cleanSubdomain = cleanSubdomain.slice(0, -1);
    }
    
    // Удаляем точку в начале домена, если она есть
    let cleanDomain = trimmedDomain;
    if (cleanDomain.startsWith('.')) {
        cleanDomain = cleanDomain.slice(1);
    }
    
    // Формируем полный URL
    return `https://${cleanSubdomain}.${cleanDomain}`;
}