// This file is released under the 3-clause BSD license. See COPYING-BSD.
function builder_gw_cpp()
    WITHOUT_AUTO_PUTLHSVAR = %t;
    copyfile("../common.h",TMPDIR);
    copyfile("../common.cpp",TMPDIR);
tbx_build_gateway("skeleton_cpp9990", ..
    ["imread","opencv_imread"], ..
    ["opencv_imread.cpp"], ..
    get_absolute_file_path("builder_gateway_cpp.sce"),[],"g++ -ggdb `pkg-config --cflags opencv` -o `basename opencv_imread.cpp .cpp` opencv_imread.cpp `pkg-config --libs opencv`");

endfunction

builder_gw_cpp();
clear builder_gw_cpp; // remove builder_gw_cpp on stack
