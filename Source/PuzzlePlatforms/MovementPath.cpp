// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementPath.h"
#include "MovingPlatform.h"
#include "DrawDebugHelpers.h"
// Sets default values for this component's properties
UMovementPath::UMovementPath()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//m_ParentPlatform->m_FT_Destination
	// ...
}


// Called when the game starts
void UMovementPath::BeginPlay()
{
	Super::BeginPlay();
	SetParentPointers();
	SetInitialStartAndFinish();

	// ...
	
}


// Called every frame
void UMovementPath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(m_ParentPlatform!=nullptr)Move(DeltaTime);
	// ...
}

void UMovementPath::SetInitialStartAndFinish()
{


	m_FTStart.SetLocation(m_ParentPlatform->GetActorLocation());
	//m_FTStart.SetRotation(m_ParentPlatform->GetActorRotation().Quaternion());

	m_FTFinish.SetLocation(m_ParentPlatform->GetTargetLocation()+m_ParentPlatform->m_FT_Destination.GetLocation());
	UE_LOG(LogTemp,Warning,TEXT("destinationlocation: %s"),*m_ParentPlatform->m_FT_Destination.GetLocation().ToString());
	//m_FTFinish.SetRotation(m_ParentPlatform->m_FT_Destination.GetRotation());

	m_FTStart.SetRotation((m_FTFinish.GetLocation() - m_FTStart.GetLocation()).GetSafeNormal().ToOrientationQuat());

	m_FV_CurrentLocation = m_FTStart.GetLocation();

	DrawDebugLine(GetWorld(), m_FTStart.GetLocation(), m_FTFinish.GetLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), m_FTStart.GetLocation(), m_FTStart.GetLocation()+m_FTStart.GetRotation().Vector().GetSafeNormal()*300.f, FColor::Red, true);

}

void UMovementPath::SetParentPointers()
{
	m_ParentActor = this->GetOwner();
	check(m_ParentActor);
	m_ParentPlatform = Cast<AMovingPlatform>(m_ParentActor);
	check(m_ParentPlatform);
}

void UMovementPath::UpdateLocation()
{
	m_FV_CurrentLocation = m_ParentPlatform->GetActorLocation();
}

void UMovementPath::Move(float DeltaTime)
{
	UpdateLocation();
	m_ParentPlatform->SetActorLocation(m_FV_CurrentLocation + m_FTStart.GetRotation().Vector().GetSafeNormal() * m_f_MovementSpeed* DeltaTime);
}
