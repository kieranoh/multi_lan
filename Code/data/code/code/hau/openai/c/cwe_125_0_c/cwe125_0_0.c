int get_price_at_index(int* prices, int size, char* index_str) {
    // 변환된 인덱스를 저장할 변수
    int index;
    
    // 문자열을 정수로 변환
    index = atoi(index_str);
    
    // 인덱스 유효성 검사
    if (index < 0 || index >= size) {
        // 유효하지 않은 인덱스의 경우 -1 반환
        return -1; 
    }
    
    // 해당 인덱스의 가격 반환
    return prices[index];
}