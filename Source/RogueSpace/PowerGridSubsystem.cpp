// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerGridSubsystem.h"
#include "PowerSystemComponent.h"
// PowerGridSubsystem.cpp
#include "PowerGridSubsystem.h"
#include "PowerSystemComponent.h"

void UPowerGridSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPowerGridSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UPowerGridSubsystem::RegisterProducer(UPowerSystemComponent* Producer)
{
	Producers.AddUnique(Producer);
	RecalculateGrid();
}

void UPowerGridSubsystem::RegisterConsumer(UPowerSystemComponent* Consumer)
{
	Consumers.AddUnique(Consumer);
	RecalculateGrid();
}

void UPowerGridSubsystem::Unregister(UPowerSystemComponent* Component)
{
	Producers.Remove(Component);
	Consumers.Remove(Component);
	RecalculateGrid();
}

void UPowerGridSubsystem::RecalculateGrid()
{
float TotalSupply = 0.0f;   //Total power supply is 0
	for (const TObjectPtr<UPowerSystemComponent>& Producer : Producers) //For each CONST REFERENCE to Producer : Producers (marked by the &, a reference to the actual element in the array, not copying it out of there; more efficient) (This pointer is CONST, not the element in the array)
	{
		if (Producer && Producer->bIsFunctional) //null protection &&
		{
			TotalSupply += Producer->PowerAmount;
		}
	}
}