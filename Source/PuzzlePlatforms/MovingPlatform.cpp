// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "MovementPath.h"

void AMovingPlatform::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	FMovementPath Person;
	Person.Age = 3;
}

void AMovingPlatform::Tick(float DeltaSeconds)
{

}
