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
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr)
		return;
	FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
	physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr)
		return;

	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * reach;

	DrawDebugLine(GetWorld(), start, end, FColor::Blue);

	FHitResult hitResult;
	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	DrawDebugSphere(GetWorld(), end, 10, 16, FColor::Blue, false, 5.0f);
	bool hasHit = GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_GameTraceChannel1, sphere);
	if (hasHit)
	{
		physicsHandle->GrabComponentAtLocationWithRotation(hitResult.GetComponent(),
			NAME_None, hitResult.ImpactPoint, hitResult.GetComponent()->GetComponentRotation());
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

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle Component found on %s"), *GetOwner()->GetName());
	}
	return result;
}