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
	// Deliberately empty for now — this is the priority-ordered distribution
	// logic, the actual interesting design surface. Filling it in next.
}