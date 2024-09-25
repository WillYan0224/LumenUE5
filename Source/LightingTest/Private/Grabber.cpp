// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	/*UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Physics Handle Found: %s"), *physicsHandle->GetName());	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle Not Found!"));
	}*/
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UGrabber::Grab()
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * reach;


	DrawDebugLine(GetWorld(), start, end, FColor::Blue);

	FHitResult hitResult;
	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	DrawDebugSphere(GetWorld(), end, 10, 16, FColor::Blue, false, 5.0f);
	bool hasHit = GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_GameTraceChannel1, sphere);
	if (hasHit)
	{
		DrawDebugSphere(GetWorld(), hitResult.Location, 10, 10, FColor::Green, false, 5.0f);
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Red, false, 5.0f);
		AActor* hitActor = hitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *hitActor->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Actor Hit!"));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Release Grabber!"));
}