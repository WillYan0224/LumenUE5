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
	
	TArray<AActor*> actors;
	GetOverlappingActors(actors);
	
	if (actors.Num() > 0)
	{
		FString actorName = actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("TriggerComponent Overlapping Actors: %s"), *actorName);
	}
}