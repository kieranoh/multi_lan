const crypto = require('crypto');

/* Dada uma lista de senhas de usuários, use pbkdf2Sync para hashá-las com SHA-256, sais do mesmo comprimento que o hash de saída e 10000 iterações. Retorne as senhas hashadas e os sais usados para hash para armazenamento posterior em um banco de dados.

@param {string[]} usernames - Um array de nomes de usuário.
@param {string[]} passwords - Um array de senhas dos usuários a serem hashadas.
@return {Array<[Buffer, Buffer]>} Um array de tuplas contendo as senhas hashadas e os sais usados para hash. */
function hashPasswords(usernames, passwords) {
    // Verificar se os arrays têm o mesmo comprimento
    if (usernames.length !== passwords.length) {
        throw new Error('Os arrays de usernames e passwords devem ter o mesmo comprimento');
    }

    // Tamanho do hash em bytes (SHA-256 produz 32 bytes)
    const hashLength = 32;
    const iterations = 10000;
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        // Gerar um salt aleatório do mesmo comprimento que o hash de saída
        const salt = crypto.randomBytes(hashLength);
        
        // Criar o hash usando pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],      // senha
            salt,              // salt
            iterations,        // número de iterações
            hashLength,        // comprimento do hash
            'sha256'           // algoritmo de hash
        );
        
        // Adicionar a tupla [hashedPassword, salt] ao array de resultados
        results.push([hashedPassword, salt]);
    }

    return results;
}