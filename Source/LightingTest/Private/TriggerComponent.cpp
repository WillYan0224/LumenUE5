// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("TriggerComponent BeginPlay"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* actor = GetAcceptableActor();
	if (actor)
	{
		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component)
		{
			component->SetSimulatePhysics(false);
		}
		actor->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		mover->SetShouldMove(true);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Nothing is overlapping"));
		mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);
	for (AActor* actor : actors)
	{
		bool hasAcceptableTag = actor->ActorHasTag(actorTag);
		bool isGrabbed = actor->ActorHasTag(FName("Grabbed"));
		if (hasAcceptableTag && !isGrabbed)
		{
			return actor;
		}
	}
	return nullptr;
}
