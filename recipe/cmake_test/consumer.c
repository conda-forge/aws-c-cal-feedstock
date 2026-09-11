#include <aws/cal/cal.h>
#include <aws/cal/hash.h>
#include <aws/common/allocator.h>
#include <aws/common/byte_buf.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    static const unsigned char expected[32] = {
        0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
        0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad
    };
    unsigned char storage[32];
    struct aws_allocator *allocator = aws_default_allocator();
    struct aws_byte_cursor input = aws_byte_cursor_from_c_str("abc");
    struct aws_byte_buf output = aws_byte_buf_from_empty_array(storage, sizeof(storage));
    aws_cal_library_init(allocator);
    if (aws_sha256_compute(allocator, &input, &output, 0)) return 1;
    if (output.len != sizeof(expected) || memcmp(output.buffer, expected, sizeof(expected))) return 2;
    aws_cal_library_clean_up();
    puts("Installed AWS crypto SHA-256 known-answer test passed");
    return 0;
}
