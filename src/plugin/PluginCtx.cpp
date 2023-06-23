#include "PluginCtx.h"
#include <al/Library/Base/String.h>
#include <al/Library/Resource/Resource.h>
#include <nn/fs.h>
#include <heap/seadExpHeap.h>
#include <heap/seadHeapMgr.h>

void PluginCtx::setContext(const LoaderCtx& ctx) {
    auto& inst = instance();
    inst.mRootPluginHeap = ctx.mRootPluginHeap;
    inst.mRomfsRootPath.format("%s/romfs", ctx.mLoadDir);
}

sead::Heap* PluginCtx::createPluginHeap(size_t size) {
    return instance().mPluginHeap = sead::ExpHeap::create(size, PLUGIN_NAME "Heap", instance().mRootPluginHeap, 8, sead::Heap::cHeapDirection_Forward, false);
}

void* PluginCtx::alloc(size_t size) { return instance().mPluginHeap->alloc(size); }
void PluginCtx::free(void* ptr) { return instance().mPluginHeap->free(ptr); }
void* PluginCtx::realloc(void* ptr, size_t size) { return instance().mPluginHeap->tryRealloc(ptr, size, sizeof(void*)); }

al::Resource* PluginCtx::findOrCreateResource(const sead::SafeString& name, const char* ext) {
    sead::ScopedCurrentHeapSetter setter(instance().mPluginHeap);
    int fullPathLen = (instance().mRomfsRootPath.calcLength() + name.calcLength()) + 2; // 1 extra for '/' char, and another for null terminator
    char fullPathBuffer[fullPathLen];
    sprintf(fullPathBuffer, "%s/%s", instance().mRomfsRootPath.cstr(), name.cstr());
    return al::findOrCreateResource(fullPathBuffer, ext);
}

al::Resource* PluginCtx::createResource(const sead::SafeString& name) {
    int fullPathLen = (instance().mRomfsRootPath.calcLength() + name.calcLength()) + 2; // 1 extra for '/' char, and another for null terminator
    char fullPathBuffer[fullPathLen];
    sprintf(fullPathBuffer, "%s/%s", instance().mRomfsRootPath.cstr(), name.cstr());
    return new(instance().mPluginHeap) al::Resource(fullPathBuffer);
}