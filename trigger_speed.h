#include "cbase.h"
#include "triggers.h"

class CTriggerSpeed : public CBaseTrigger
{
  DECLARE_CLASS(CTriggerSpeed, CBaseTrigger);

  public:
  void Spawn(void);
  void StartTouch(CBaseEntity *pOther);
  void EndTouch(CBaseEntity *pOther);
  bool TestSpeed(CBaseEntity *pActivator);
  void TeleportActivator(CBaseEntity *pActivator);

  DECLARE_DATADESC();
  private:
  float m_fSpeed;
};
