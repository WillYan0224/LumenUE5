// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCompoentTest.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCompoentTest::AMyCompoentTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera component (Root)
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	RootComponent = CameraComponent;

	// Light Componemt
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SpotLightComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotLightComponent->SetIntensity(5000.0f);
	SpotLightComponent->SetLightColor(FLinearColor(1.0f, 0.0f, 0.0f));

	// SM component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AMyCompoentTest::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMyCompoentTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLoc = GetActorLocation();
	CurrentLoc.Y += Speed * DeltaTime;
	SetActorLocation(CurrentLoc);

	float DistMoved = FVector::Dist(StartLocation, CurrentLoc);
	if (DistMoved > MoveDistance)
	{
		Speed = -Speed;
	}
}

