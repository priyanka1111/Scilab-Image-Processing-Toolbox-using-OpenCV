// This file is released under the 3-clause BSD license. See COPYING-BSD.
function builder_gw_cpp()
    copyfile("../common.h",TMPDIR);
    copyfile("../common.cpp",TMPDIR);
    WITHOUT_AUTO_PUTLHSVAR = %t;
tbx_build_gateway("skeleton_cpp3451", ..
    ["getStructuringElement","getStructuringElement"], ..
    ["getStructuringElement.cpp"], ..
    get_absolute_file_path("builder_gateway_cpp.sce"),[],"g++ -ggdb `pkg-config --cflags opencv` -o `basename getStructuringElement.cpp .cpp` getStructuringElement.cpp `pkg-config --libs opencv`");

endfunction

builder_gw_cpp();
clear builder_gw_cpp; // remove builder_gw_cpp on stack
