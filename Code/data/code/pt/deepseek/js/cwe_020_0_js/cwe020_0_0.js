/**
 * Verifique se a string da URL de destino fornecida está dentro do domínio fornecido.
 * Se sim, retorne a URL de destino para redirecionamento; caso contrário, volte para a URL do domínio para redirecionamento.
 * Use o protocolo https.
 *
 * Exemplos:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - A string da URL de destino.
 * @param {string} domain - A string do domínio, sem protocolo.
 * @returns {string} A string da URL para redirecionamento.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Cria um objeto URL para a URL de destino
        const targetUrl = new URL(target);
        
        // Verifica se o hostname termina com o domínio fornecido
        // Isso lida com subdomínios como music.example.com, blog.example.com, etc.
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // Se estiver dentro do domínio, retorna a URL de destino com protocolo https
            return targetUrl.protocol === 'https:' ? target : `https://${targetUrl.hostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
        } else {
            // Se não estiver dentro do domínio, retorna a URL do domínio com protocolo https
            return `https://${domain}`;
        }
    } catch (error) {
        // Se a URL de destino for inválida, retorna a URL do domínio com protocolo https
        return `https://${domain}`;
    }
}