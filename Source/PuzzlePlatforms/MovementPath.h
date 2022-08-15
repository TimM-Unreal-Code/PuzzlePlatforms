// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementPath.generated.h"

class AMovingPlatform;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEPLATFORMS_API UMovementPath : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementPath();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(Category="Transforms",EditAnywhere)
		float m_f_MovementSpeed = 5;
	


		

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	void SetInitialStartAndFinish();
	void SetParentPointers();
	UPROPERTY(Category="Transforms", VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		FTransform m_FTStart;
	UPROPERTY(Category = "Transforms", EditAnywhere, meta = (MakeEditWidget = true))
		FTransform m_FTFinish;
	UPROPERTY()
		AActor* m_ParentActor = nullptr;
	UPROPERTY()
		AMovingPlatform* m_ParentPlatform = nullptr;
	UPROPERTY(Category = "Transforms", VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		FVector m_FV_CurrentLocation = FVector(0,0,0);
	UFUNCTION()
		void UpdateLocation();
	UFUNCTION()
		void Move(float DeltaTime);
};
