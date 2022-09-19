#!/bin/sh

FILES="
../imgui/imconfig.h
../imgui/imgui.cpp
../imgui/imgui.h
../imgui/imgui_demo.cpp
../imgui/imgui_draw.cpp
../imgui/misc/debuggers/imgui.natvis
../imgui/backends/imgui_impl_glfw.cpp
../imgui/backends/imgui_impl_glfw.h
../imgui/backends/imgui_impl_opengl3.cpp
../imgui/backends/imgui_impl_opengl3.h
../imgui/backends/imgui_impl_opengl3_loader.h
../imgui/imgui_internal.h
../imgui/imgui_tables.cpp
../imgui/imgui_widgets.cpp
../imgui/imstb_rectpack.h
../imgui/imstb_textedit.h
../imgui/imstb_truetype.h
../implot/implot.cpp
../implot/implot.h
../implot/implot_demo.cpp
../implot/implot_internal.h
../implot/implot_items.cpp
"
for i in $FILES; do 
    cp -v $i imgui/.
done
