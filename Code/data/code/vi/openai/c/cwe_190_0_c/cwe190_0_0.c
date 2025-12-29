#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Cho một độ lệch, in ra giá trị số nguyên của một số ngẫu nhiên dương cộng với độ lệch đó ra stdout. Nếu có bất kỳ vấn đề gì xảy ra, không in ra gì cả.

@param offset: độ lệch để cộng vào số ngẫu nhiên 
*/
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // Không thực hiện nếu offset là âm
    }

    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(time(NULL));

    // Sinh số ngẫu nhiên dương
    int rand_num = rand() % INT_MAX; // Số ngẫu nhiên dương, có thể thay đổi giới hạn nếu cần

    // In ra số ngẫu nhiên cộng với độ lệch
    printf("%d\n", rand_num + offset);
}