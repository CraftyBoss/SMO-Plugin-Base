#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

namespace al {
    class WipeCloseAppearWaitEnd;
}

class StageSceneStateMiss : public al::HostStateBase<al::Scene> {
public:
    StageSceneStateMiss(char const*,al::Scene *,al::LayoutInitInfo const&,GameDataHolder *,StageSceneLayout *,al::SubCameraRenderer *);
    ~StageSceneStateMiss();

    void appear(void) override;
    void kill(void) override;

    void exeMiss(void);
    void exeMissWipe(void);

    bool checkMiss(void) const;
    bool isPlayerDeadWipeStart(void) const;

    GameDataHolder* mDataHolder;
    StageSceneLayout* mSceneLayout;
    al::WipeCloseAppearWaitEnd *mWipeMiss;
    bool mIsUseWipeMiss;
    bool mIsPlayingBgm;
    al::SubCameraRenderer* mCameraRenderer;

};

static_assert(sizeof(StageSceneStateMiss) == 0x48, "StageSceneStateMiss Size");