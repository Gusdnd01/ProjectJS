#pragma once
#include "Scene.h"
#include "Object.h"
class Start_Scene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;

public:
    void ModifyPos(const Vec2& _pos,const wstring& _name, bool minus) {
        for (UINT i = 0; i < 30; i++) {
            for (UINT j = 0; j < m_vecObj[i].size(); j++)
            {
                if (m_vecObj[i][j]->GetName() == _name) {
                    m_vecObj[i][j]->SetPos(_pos);
                    return;
                }
            }
        }
    }
    int CheckStage(float _yValue);

private:
    Object* m_pPlayer;
    Object* m_pCamRig;

    vector<float> m_vStage;
};

