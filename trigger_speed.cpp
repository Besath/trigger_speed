#include "trigger_speed.h"

LINK_ENTITY_TO_CLASS(trigger_speed, CTriggerSpeed);

BEGIN_DATADESC(CTriggerSpeed)
  DEFINE_KEYFIELD(m_fSpeed, FIELD_FLOAT, "speed")
END_DATADESC()

void CTriggerSpeed::Spawn(void)
{
  BaseClass::Spawn();
  InitTrigger();
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity starts touching us.
// Input  : pOther - The entity that is touching us.
//-----------------------------------------------------------------------------
void CTriggerSpeed::StartTouch(CBaseEntity *pOther)
{
  if (!TestSpeed(pOther))
  {
    TeleportActivator(pOther);
    return;
  }

  BaseClass::StartTouch(pOther);	
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity stops touching us.
// Input  : pOther - The entity that was touching us.
//-----------------------------------------------------------------------------
void CTriggerSpeed::EndTouch(CBaseEntity *pOther)
{
  if (!TestSpeed(pOther))
  {
    TeleportActivator(pOther);
    return;
  }

  BaseClass::EndTouch(pOther);	
}

//----------------------------------------------------------------------------
// Purpose: Test if the activator is moving slower than allowed
// Input  : pActivator - the entity that touched us
//----------------------------------------------------------------------------
bool CTriggerSpeed::TestSpeed(CBaseEntity *pActivator)
{
  Vector vel(0, 0, 0);
  vel = pActivator->GetLocalVelocity();
  return vel.Length() < m_fSpeed;
}

//----------------------------------------------------------------------------
// Purpose: Teleport activator to the target destination
// Input  : pActivator - the entity that touched us
//----------------------------------------------------------------------------
void CTriggerSpeed::TeleportActivator(CBaseEntity *pActivator)
{
  CBaseEntity *pentTarget = NULL;

  pentTarget = gEntList.FindEntityByName(pentTarget, m_target, NULL, pActivator, pActivator);

  if (!pentTarget)
  {
    return;
  }

  pActivator->SetGroundEntity(NULL);
  Vector tmp = pentTarget->GetAbsOrigin();

  if (pActivator->IsPlayer())
  {
    // make origin adjustments in case the teleportee is a player. (origin in center, not at feet)
    tmp.z -= pActivator->WorldAlignMins().z;
  }

  // face the direction of teleport destination
  const QAngle *pAngles = &pentTarget->GetAbsAngles();
  // make velocity a zero vector because NULL doesn't set it to zero
  Vector vecZero(0, 0, 0);
  Vector *pVelocity = &vecZero;

  pActivator->Teleport( &tmp, pAngles, pVelocity );
}
