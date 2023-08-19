// Simple Shooter Game.


#include "Animations/SSEquipFinishedAnimNotify.h"

void USSEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	
	Super::Notify(MeshComp, Animation);
}
