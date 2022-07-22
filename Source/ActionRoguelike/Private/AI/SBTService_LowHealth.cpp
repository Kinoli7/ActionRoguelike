// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_LowHealth.h"

#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USBTService_LowHealth::USBTService_LowHealth()
{
	LowHealthThreshold = 10;
}

void USBTService_LowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between AIPawn and TargetActor
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AActor* SelfActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("SelfActor"));
		if (SelfActor)
		{
			USAttributeComponent* AttributeComp = SelfActor->FindComponentByClass<USAttributeComponent>();
			if (AttributeComp)
			{
				BlackBoardComp->SetValueAsBool("IsLowHealth", LowHealthThreshold >= AttributeComp->GetActualHealth());
			}
		}
	}
}
