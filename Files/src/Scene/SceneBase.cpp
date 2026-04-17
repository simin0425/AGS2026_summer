#include "SceneBase.h"

bool SceneBase::SystemInit(SCENE scene, int sub_scene)
{
    myScene_ = nextScene_ = scene;
    subScene_ = sub_scene;

    return true;
}

SceneBase::SCENE SceneBase::GetMyScene() const
{
    return myScene_;
}

SceneBase::SCENE SceneBase::GetNextScene() const
{
    return nextScene_;
}
