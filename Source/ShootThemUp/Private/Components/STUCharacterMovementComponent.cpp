#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const float MAXSPEED = Super::GetMaxSpeed();

	const ASTUBaseCharacter* player = Cast<ASTUBaseCharacter>(GetPawnOwner());

	return player && player->isRunning() ? MAXSPEED * RunModifier : MAXSPEED;
}