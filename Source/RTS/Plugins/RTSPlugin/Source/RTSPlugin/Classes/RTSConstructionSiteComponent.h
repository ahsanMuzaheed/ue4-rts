#pragma once

#include "RTSPluginPrivatePCH.h"

#include "Components/ActorComponent.h"

#include "RTSConstructionSiteComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSConstructionSiteComponentConstructionStartedSignature, float, TotalConstructionTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRTSConstructionSiteComponentConstructionFinishedSignature);


/** Allows constructing the actor over time. */
UCLASS(meta = (BlueprintSpawnableComponent))
class URTSConstructionSiteComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Builders currently working at this construction site. */
	TArray<AActor*> AssignedBuilders;

	/** Time for constructing the actor, in seconds. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS")
	float ConstructionTime;

	/** Time before the actor is constructed, in seconds. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS", replicated)
	float RemainingConstructionTime;

	/** Whether builders are required for making construction progress, or the building is constructed automatically. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS")
	bool bRequiresBuilderAttention;

	/** Whether to start construction immediately after spawn, or not. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS")
	bool bStartImmediately;


	URTSConstructionSiteComponent(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


	/** Gets the current construction progress [0..1]. */
	UFUNCTION(BlueprintCallable)
	float GetProgressPercentage() const;

	/** Whether the construction timer is currently being ticked, or not. */
	UFUNCTION(BlueprintCallable)
	bool IsConstructing() const;

	/** Starts constructing the actor, setting the timer. */
	UFUNCTION(BlueprintCallable)
	void StartConstruction();


	/** Event when the construction timer has been started. */
	UPROPERTY(BlueprintAssignable, Category = "RTS")
	FRTSConstructionSiteComponentConstructionStartedSignature OnConstructionStarted;

	/** Event when the construction timer has been expired. */
	UPROPERTY(BlueprintAssignable, Category = "RTS")
	FRTSConstructionSiteComponentConstructionFinishedSignature OnConstructionFinished;

private:
	/** Whether the construction timer is currently being ticked, or not. */
	bool bConstructing;
};
