#pragma once

#include "EventHolders.h"
#include <game/HakoniwaSequence/HakoniwaSequence.h>
#include <game/System/GameSystem.h>
#include <game/Player/PlayerActorHakoniwa.h>


namespace GameSystemEvent {
    CREATE_HOOK_EVENT_ARGS(Init, "_ZN10GameSystem4initEv", GameSystem*)
}

namespace HakoniwaSequenceEvent {
    CREATE_HOOK_EVENT_ARGS(Init, "_ZN16HakoniwaSequence4initERKN2al16SequenceInitInfoE", HakoniwaSequence*, al::SequenceInitInfo const&)
    CREATE_HOOK_EVENT_ARGS(Update, "_ZN16HakoniwaSequence6updateEv", HakoniwaSequence*)
    // Nerves
    CREATE_HOOK_EVENT_ARGS(Destroy, "_ZN16HakoniwaSequence10exeDestroyEv", HakoniwaSequence*)
}

namespace StageSceneEvent {
    CREATE_HOOK_EVENT_ARGS(Init, "_ZN10StageScene4initERKN2al13SceneInitInfoE", StageScene*, al::SceneInitInfo const&)
    CREATE_HOOK_EVENT_ARGS(Control, "_ZN10StageScene7controlEv", StageScene*)
    CREATE_HOOK_EVENT_ARGS(Kill, "_ZN10StageScene4killEv", StageScene*)
    CREATE_HOOK_EVENT_ARGSR(UpdatePlay, "_ZN10StageScene10updatePlayEv", bool, StageScene*)
}

namespace PlayerEvent {
    CREATE_HOOK_EVENT_ARGS(Movement, "_ZN19PlayerActorHakoniwa8movementEv", PlayerActorHakoniwa*)
    CREATE_HOOK_EVENT_ARGSR(ReceiveMsg, "_ZN19PlayerActorHakoniwa10receiveMsgEPKN2al9SensorMsgEPNS0_9HitSensorES5_", bool,
                            PlayerActorHakoniwa*, al::SensorMsg*, al::HitSensor*, al::HitSensor*)
}

namespace ModEvent {
    CREATE_MOD_EVENT(ImguiDraw)
    CREATE_MOD_EVENT(OnPlayerDamage)
}