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
    const url = new URL(target);
    const targetDomain = url.hostname;
    const baseDomain = domain.startsWith('www.') ? domain.slice(4) : domain;

    if (targetDomain.endsWith(baseDomain) || targetDomain === baseDomain) {
        return target;
    } else {
        return `https://${baseDomain}`;
    }
}