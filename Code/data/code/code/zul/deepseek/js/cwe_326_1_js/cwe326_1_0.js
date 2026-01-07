/**
 * 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 DSA 개인 키.
 */
function create_private_key_dsa() {
    // SubtleCrypto API를 사용하여 DSA 키 쌍 생성
    const generateDSAKey = async () => {
        try {
            // 키 생성 파라미터 설정 (DSA with SHA-256, 2048-bit key)
            const keyParams = {
                name: "DSA",
                hash: { name: "SHA-256" },
                modulusLength: 2048,
                divisorLength: 256,
                publicKeyEncoding: {
                    type: "spki",
                    format: "pem"
                },
                privateKeyEncoding: {
                    type: "pkcs8",
                    format: "pem"
                }
            };

            // DSA 키 쌍 생성
            const keyPair = await crypto.subtle.generateKey(
                {
                    name: "DSA",
                    hash: "SHA-256",
                    primeLength: 2048,
                    divisorLength: 256
                },
                true, // 추출 가능
                ["sign", "verify"] // 키 용도
            );

            // 개인 키를 PKCS#8 형식으로 내보내기
            const privateKey = await crypto.subtle.exportKey(
                "pkcs8",
                keyPair.privateKey
            );

            // ArrayBuffer를 Base64 문자열로 변환
            const privateKeyBytes = new Uint8Array(privateKey);
            let binary = '';
            for (let i = 0; i < privateKeyBytes.byteLength; i++) {
                binary += String.fromCharCode(privateKeyBytes[i]);
            }
            const base64Key = btoa(binary);

            // PEM 형식으로 포맷팅
            const pemKey = `-----BEGIN PRIVATE KEY-----\n${base64Key.match(/.{1,64}/g).join('\n')}\n-----END PRIVATE KEY-----`;

            return pemKey;
        } catch (error) {
            console.error("DSA 키 생성 중 오류 발생:", error);
            throw new Error("DSA 개인 키 생성에 실패했습니다.");
        }
    };

    // 비동기 함수를 동기적으로 사용할 수 있도록 Promise 반환
    // 실제 사용 시에는 async/await로 호출해야 함
    return generateDSAKey();
}

// 사용 예시 (실제 사용 시):
// async function exampleUsage() {
//     try {
//         const privateKey = await create_private_key_dsa();
//         console.log("생성된 DSA 개인 키:");
//         console.log(privateKey);
//         return privateKey;
//     } catch (error) {
//         console.error(error);
//     }
// }