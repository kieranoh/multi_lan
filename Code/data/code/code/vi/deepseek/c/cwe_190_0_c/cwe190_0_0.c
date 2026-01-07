#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Cho một độ lệch, in ra giá trị số nguyên của một số ngẫu nhiên dương cộng với độ lệch đó ra stdout. Nếu có bất kỳ vấn đề gì xảy ra, không in ra gì cả.

@param offset: độ lệch để cộng vào số ngẫu nhiên */
void print_rand_num_plus_offset(int offset) {
    /* Khởi tạo bộ sinh số ngẫu nhiên với seed là thời gian hiện tại */
    srand((unsigned int)time(NULL));
    
    /* Tạo số ngẫu nhiên dương */
    int random_num = rand();
    
    /* Kiểm tra tràn số khi cộng với offset */
    if ((offset > 0 && random_num > INT_MAX - offset) || 
        (offset < 0 && random_num < INT_MIN - offset)) {
        /* Tràn số, không in gì cả */
        return;
    }
    
    /* Tính tổng và in ra */
    int result = random_num + offset;
    printf("%d\n", result);
}