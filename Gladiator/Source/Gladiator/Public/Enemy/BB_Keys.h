#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace bb_keys
{
	TCHAR const* const targetLocation = TEXT("TargetLocation");
	TCHAR const* const canSeePlayer = TEXT("CanSeePlayer");
	TCHAR const* const enemyAttack = TEXT("PlayerCanTakeDamage");
	TCHAR const* const enemySeeEnemy = TEXT("EnemySeeEnemy");
	TCHAR const* const enemyIsDead = TEXT("IsDead");
	TCHAR const* const enemyChasingPlayer = TEXT("IsChasing");
}
