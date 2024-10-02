#ifndef WSTRING_H
#define WSTRING_H

#include <stdint.h>
#include <wchar.h>

typedef struct wstring {
    uint32_t unk_0x0;  // 0x00
    wchar_t str[8];    // 0x04
    wchar_t* pointer;   // 0x14
    uint32_t length;    // 0x18
    uint32_t length2;   // 0x1C
} wstring;


typedef void (*wstring_constructor_t)(wstring* self, const wchar_t* str);
typedef void (*wstring_assign_w_t)(wstring* self, const wchar_t* _str, int _length);
typedef void (*wstring_assign_c_t)(wstring* self, const char* _str, int _length);
typedef int (*wstring_compare_t)(const wchar_t* str1, const wchar_t* str2);

extern void wstring_init(wstring* self, const wchar_t* str) ; //81972508
extern const wstring* wstring_assign_w(wstring* self, const wchar_t* _str, int _length) ;
extern const wstring* wstring_assign_c(wstring* self, const char* _str, int _length) ;
extern int wstring_equals(const wstring* self, const wchar_t* _str) ;

// assign__Q2_3std78basic_string__tm__58_wQ2_3std20char_traits__tm__2_wQ2_3std18allocator__tm__2_wFPCZ1ZQ4_3std25_String_val__tm__7_Z1ZZ3Z5_Alty9size_type_RQ2_3std30basic_string__tm__10_Z1ZZ2ZZ3Z_26
//0x030E8BC4  > FUN_81a5d5d8 ?


//assign__Q2_3std78basic_string__tm__58_cQ2_3std20char_traits__tm__2_cQ2_3std18allocator__tm__2_cFPCZ1ZQ4_3std25_String_val__tm__7_Z1ZZ3Z5_Alty9size_type_RQ2_3std30basic_string__tm__10_Z1ZZ2ZZ3Z_22(
//0x02e33e08 > FUN_815e35d0 ?



#endif
