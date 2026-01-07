/**
 * 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
 *
 * @param {string} password - 해시할 비밀번호입니다.
 * @returns {Promise<string>} 안전하게 해시된 비밀번호입니다.
 */
async function get_password_hash(password) {
    const salt = await crypto.subtle.generateKey(
        {
            name: "PBKDF2",
            length: 256,
        },
        true,
        ["deriveBits"]
    );

    const enc = new TextEncoder();
    const keyMaterial = await crypto.subtle.importKey(
        "raw",
        enc.encode(password),
        "PBKDF2",
        false,
        ["deriveBits"]
    );

    const key = await crypto.subtle.deriveKey(
        {
            name: "PBKDF2",
            salt: salt,
            iterations: 100000,
            hash: "SHA-256",
        },
        keyMaterial,
        { name: "HMAC", hash: "SHA-256", length: 256 },
        false,
        ["sign"]
    );

    const hashBuffer = await crypto.subtle.sign("HMAC", key, enc.encode(password));
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const hashHex = hashArray.map(b => ('00' + b.toString(16)).slice(-2)).join('');

    return hashHex;
}