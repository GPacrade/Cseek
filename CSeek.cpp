#include <string.h>
#include <cstdint>
#include <cstdlib>
#include "syntax.h"
#include "eatos.h"
void help(void) {
    printf("\n\t~~=CSeek=~~\n\n\t [file path] [mode]\n\n");
}
/// <summary>
/// starting point
/// </summary>
void argument_parser(int agrc, const wchar_t** agrv) {
    FILE* file;
    _wfopen_s(&file, agrv[0], L"rb");
    size_t syntax_size = 30;
    size_t syntax_used = 0;
    points* syntax_stack = (points*)malloc(syntax_size * sizeof(points));
    char* read_buffer = (char*)malloc(4028 * sizeof(char));
    bool t_symboi = 0;
    bool in_str = 0;
    bool change_space=0;
    bool is_last = 0;
    size_t read_buffer_size = 0;
    error err;
    eatos eatos_data;
    space global_space;
    if(file&&read_buffer)
    while (read_buffer_size = fread(read_buffer, 1, 4028, file)) {
        for (size_t i = 0; i < read_buffer_size; i++) {
            if (read_buffer_size != 4028 && (i + 1 >= read_buffer_size))is_last = 1;
            err.poi.line++;
            err.poi.val= read_buffer[i],
            syntax(
                read_buffer[i],
                syntax_stack,  syntax_size,
                syntax_used,  t_symboi,
                in_str,  change_space,
                err,  is_last, eatos_data,global_space
            );
            err.out();
            if (read_buffer[i] == '\n') {
                err.poi.line = 0;
                err.poi.colum++;
            }
        }
    }
    else {
        err.out("CSEEK: fail read file, file cannon open or cannont aloc bufer");
        err.out();
    }
}


int main() {
    const wchar_t** test= (const wchar_t**)malloc(1 * sizeof(const wchar_t*));
    test[0] = L"C:\\Users\\GParcade\\Desktop\\test.txt";
    argument_parser(1, test);
}
//int wmain(int agrc, const wchar_t** agrv) {
//    if (agrc == 1) help();
//    else argument_parser(agrc - 1, ++agrv);
//    return 0;
//}