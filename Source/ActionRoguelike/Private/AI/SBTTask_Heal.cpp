// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"

USBTTask_Heal::USBTTask_Heal()
{
	HealValue = 50;
}

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		USAttributeComponent* AttributeComp = MyPawn->FindComponentByClass<USAttributeComponent>();
		if (AttributeComp->GetActualHealth() <= 10.0f)
		{
			AttributeComp->ApplyHealthChange(MyPawn, 80.0f);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
		
	}
	
	return EBTNodeResult::Failed; 
}
