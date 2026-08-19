// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerSystemComponent.generated.h"

UENUM( BlueprintType )
enum class EPowerRole : uint8
{
	Producer, 
	Consumer
};

UCLASS( ClassGroup=(ShipSystems), meta=(BlueprintSpawnableComponent) )
class ROGUESPACE_API UPowerSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPowerSystemComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Power")
	EPowerRole Role = EPowerRole::Consumer;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Power")
	float PowerAmount = 10.f;
	
	UPROPERTY(ReplicatedUsing=OnRep_IsPowered, BlueprintReadOnly, Category="Power")
	bool bIsPowered = true;
	
	UPROPERTY(ReplicatedUsing=OnRep_IsFunctional, BlueprintReadOnly, Category="Power")
	bool bIsFunctional = true;
		
	UFUNCTION(BlueprintCallable, Category="Power") 
	void Repair();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;  //virtual means this function can be overridden by a derived class. C++ looks up which version to run based on object's real type at runtime.
	
	UFUNCTION() 
	void OnRep_IsPowered();
	
	UFUNCTION() 
	void OnRep_IsFunctional();

	// Called by the subsystem when this consumer's supply status changes
	friend class UPowerGridSubsystem;
	void SetPowered(bool bNewPowered);

	UFUNCTION(BlueprintImplementableEvent, Category="Power")
	void OnPowerLost();

	UFUNCTION(BlueprintImplementableEvent, Category="Power")
	void OnPowerRestored();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Power")
	void OnFunctionRestored();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Power")
	void OnFunctionLost();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
