#include "logger/Logger.hpp"
#include "plugin/events/Events.h"
#include "types.h"
#include <imgui.h>
#include <plugin/PluginCtx.h>

// change size as needed for your plugin
#define PLUGIN_HEAP_SIZE 0x10000 // equal to MBTOBYTES(0.0625)

void drawSizeInfo(float curSize, float maxSize, const char* name) {

    // convert size to megabytes for readability
    curSize = BYTESTOMB(curSize);
    maxSize = BYTESTOMB(maxSize);

    float progress = curSize / maxSize;

    char buf[0x60];
    sprintf(buf, "%s: %.3fmb/%.3fmb", name, curSize, maxSize);
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(0,200,0,255));
    ImGui::ProgressBar(progress, ImVec2(-FLT_MIN, 0.f), buf);
    ImGui::PopStyleColor();
}

void drawHeapInfo(sead::Heap *heap) {
    if(!heap)
        return;

    u64 size = heap->getSize();
    u64 freeSize = heap->getFreeSize();

    drawSizeInfo(size - freeSize,  size, heap->getName().cstr());
}

// gets ran once during init
extern "C" EXPORT_SYM bool plugin_main(LoaderCtx& ctx) {
    PluginCtx::setContext(ctx); // sets up plugin context from the plugin loader's context
    ctx.mChildHeap = PluginCtx::createPluginHeap(PLUGIN_HEAP_SIZE);

    // if the loader reloads all plugins (either due to a caught crash or by user),
    // use this flag to either run code that will no longer run (ex: pre/postfixes installed at an init event(s))
    // or alternatively, return false if those init events are required to be run at their respective locations
    if(ctx.mIsReload) {
        Logger::log("Welcome back!\n");
    }

    ModEvent::ImguiDraw::addEvent([]() {
        ImGui::Begin("My Plugin Window");

        if(ImGui::Button("Send Goodbye World")) {
            Logger::log("Goodbye World.\n");
        }

        ImGui::End();
    });

    // return true/false depending on whether or not the plugin was sucessfully loaded
    return true;
}

extern "C" void exl_exception_entry() {
    /* TODO: exception handling */
}