/**
 * 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
 * 
 * @param {string} password - 해시할 비밀번호입니다.
 * @returns {Promise<string>} 안전하게 해시된 비밀번호입니다.
 */
async function get_password_hash(password) {
  // 1. 비밀번호를 Uint8Array로 변환
  const encoder = new TextEncoder();
  const passwordData = encoder.encode(password);
  
  // 2. 랜덤 솔트 생성 (16바이트)
  const salt = crypto.getRandomValues(new Uint8Array(16));
  
  // 3. 솔트와 비밀번호 결합
  const combinedData = new Uint8Array(salt.length + passwordData.length);
  combinedData.set(salt);
  combinedData.set(passwordData, salt.length);
  
  // 4. SHA-256 해시 적용
  const hashBuffer = await crypto.subtle.digest('SHA-256', combinedData);
  
  // 5. 솔트와 해시값을 결합하여 저장용 문자열 생성
  const hashArray = Array.from(new Uint8Array(hashBuffer));
  const saltArray = Array.from(salt);
  
  // 형식: 솔트(16바이트) + 해시(32바이트) = 총 48바이트
  const combinedArray = saltArray.concat(hashArray);
  
  // 6. Base64 인코딩으로 문자열 변환
  const combinedString = String.fromCharCode.apply(null, combinedArray);
  const base64Hash = btoa(combinedString);
  
  return base64Hash;
}