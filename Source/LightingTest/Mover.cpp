// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetOwner()->GetActorLocation();
	
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	if (shouldMove)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mover is Ticking"));
		speed = FVector::Dist(startLocation, startLocation + moveOffset) / moveTime;
		Owner->SetActorLocation(FMath::VInterpConstantTo(Owner->GetActorLocation(), startLocation + moveOffset, DeltaTime, speed));
	}

}

void UMover::SetShouldMove(bool move)
{
	shouldMove = move;
}	

