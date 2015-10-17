// This file is released under the 3-clause BSD license. See COPYING-BSD.
function builder_gw_cpp()
    WITHOUT_AUTO_PUTLHSVAR = %t;
    copyfile("../common.h",TMPDIR);
    copyfile("../common.cpp",TMPDIR);
tbx_build_gateway("skeleton_cpp3451", ..
    ["histeq","histeq"], ..
    ["histeq.cpp"], ..
    get_absolute_file_path("builder_gateway_cpp.sce"),[],"g++ -ggdb `pkg-config --cflags opencv` -o `basename histeq.cpp .cpp` histeq.cpp `pkg-config --libs opencv`");

endfunction

builder_gw_cpp();
clear builder_gw_cpp; // remove builder_gw_cpp on stack
