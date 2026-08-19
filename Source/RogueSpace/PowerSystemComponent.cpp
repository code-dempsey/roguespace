// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSystemComponent.h"
#include "PowerGridSubsystem.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPowerSystemComponent::UPowerSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPowerSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		if (UPowerGridSubsystem* Grid = World->GetSubsystem<UPowerGridSubsystem>())
		{
			if (Role == EPowerRole::Producer)
			{
				Grid->RegisterProducer(this);
			}
			else
			{
				Grid->RegisterConsumer(this);
			}
		}
	}
	
}

void UPowerSystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (UPowerGridSubsystem* Grid = World->GetSubsystem<UPowerGridSubsystem>())
		{
			Grid->Unregister(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UPowerSystemComponent::OnRep_IsPowered()
{
		if (bIsPowered)
		{
			OnPowerRestored();
		}
		else
		{
			OnPowerLost();
		}
}
void UPowerSystemComponent::OnRep_IsFunctional()
{
	if (bIsFunctional)
	{
		OnFunctionRestored();
	}
	else
	{
		OnFunctionLost();
	}
}

void UPowerSystemComponent::Repair()
{
	if (GetOwner() && GetOwner()->HasAuthority()) //If GetOwner exists and the pointer that returns GetOwner's HasAuthority member function (checked this way to avoid a null derefence which would result in a crash)
	{
		bIsFunctional = true;
	}
}

void UPowerSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPowerSystemComponent, bIsPowered); //Registering bIsPowered for replication
	DOREPLIFETIME(UPowerSystemComponent, bIsFunctional); //Same here
}

// Called every frame
void UPowerSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

