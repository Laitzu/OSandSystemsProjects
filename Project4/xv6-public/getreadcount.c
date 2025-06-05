#include "types.h"
#include "user.h"

int main(void) {
    int readCount = getreadcount();
    printf(1, "Current readcount: %d\n", readCount);
    exit();
}
