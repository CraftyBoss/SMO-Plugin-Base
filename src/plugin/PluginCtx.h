#pragma once
#include <heap/seadHeap.h>
#include <al/Library/Resource/ResourceHolder.h>

// struct passed to each plugin to provide any needed context from the plugin loader.
// also used to return data to the loader
struct LoaderCtx {
    sead::Heap* mRootPluginHeap = nullptr;
    sead::Heap* mChildHeap = nullptr; // heap created by plugin context
    char mLoadDir[0x40] = {};
    bool mIsReload = false;
};

class PluginCtx {
    // heap that all plugins use for their own heaps.
    sead::Heap *mRootPluginHeap = nullptr;
    sead::Heap *mPluginHeap = nullptr;
    sead::FixedSafeString<0x40> mRomfsRootPath;

    static PluginCtx& instance() {
        static PluginCtx inst;
        return inst;
    }
public:
    static void setContext(const LoaderCtx& ctx);

    // memory functions

    static sead::Heap* createPluginHeap(size_t size);

    static sead::Heap* getPluginHeap() { return instance().mPluginHeap; }

    static void* alloc(size_t size);
    static void* realloc(void* ptr, size_t size);
    static void free(void* ptr);

    // file system functions

    static al::Resource* findOrCreateResource(const sead::SafeString &name, const char* ext = nullptr);

    static al::Resource* createResource(const sead::SafeString &name);
};
