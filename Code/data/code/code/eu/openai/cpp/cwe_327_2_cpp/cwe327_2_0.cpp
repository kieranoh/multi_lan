encryption_result result;

    // Hasierako bektorea (IV) sortu
    result.iv.resize(AES_BLOCK_SIZE);
    RAND_bytes(result.iv.data(), result.iv.size());

    // Gakoaren luzera eta egokitzapena
    unsigned char aes_key[AES_BLOCK_SIZE];
    std::copy(key.begin(), key.begin() + AES_BLOCK_SIZE, aes_key);

    // Datuak betetzea
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // AES enkriptatzailea hasi
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, 128, &encrypt_key); // 128 bit gakoa erabiltzen dugu

    // Enkriptatzea
    result.encrypted_data.resize(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(
            padded_data.data() + i,
            result.encrypted_data.data() + i,
            AES_BLOCK_SIZE,
            &encrypt_key,
            result.iv.data(),
            AES_ENCRYPT
        );
    }

    // Gakoa irudi gisa gorde
    result.key = std::vector<unsigned char>(aes_key, aes_key + AES_BLOCK_SIZE);

    return result;
}