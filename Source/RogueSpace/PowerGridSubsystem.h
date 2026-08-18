// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PowerGridSubsystem.generated.h"

class UPowerSystemComponent;
/**
 * 
 */
UCLASS()
class ROGUESPACE_API UPowerGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void RegisterProducer(UPowerSystemComponent* Producer);
	void RegisterConsumer(UPowerSystemComponent* Consumer);
	void Unregister(UPowerSystemComponent* Component);
	
	
protected:
	UPROPERTY()
	TArray<TObjectPtr<UPowerSystemComponent>> Producers;

	UPROPERTY()
	TArray<TObjectPtr<UPowerSystemComponent>> Consumers;

	void RecalculateGrid();
};
