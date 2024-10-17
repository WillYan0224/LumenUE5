// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraUtility.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACameraUtility::ACameraUtility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraUtility::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraUtility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float const timeBetweenCameraChanges = 2.0f;
	float const smoothBlendTime = 0.75f;

	timeToNextCameraChange -= DeltaTime;
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (OurPlayerController != nullptr)
	{
		if (OurPlayerController->WasInputKeyJustPressed(EKeys::One))
		{
			SwitchToCameraOne(timeBetweenCameraChanges, smoothBlendTime);
			UE_LOG(LogTemp, Warning, TEXT("Switching to Camera 1"))
		}
		if (OurPlayerController->WasInputKeyJustPressed(EKeys::Two))
		{
			SwitchToCameraTwo();
			UE_LOG(LogTemp, Warning, TEXT("Switching to Camera 2"))
		}
		if (OurPlayerController->WasInputKeyJustPressed(EKeys::Three))
		{
			OurPlayerController->SetViewTargetWithBlend(PlayerActor, smoothBlendTime);
			UE_LOG(LogTemp, Warning, TEXT("Switching to Character Camera"))
		}
	}
}

void ACameraUtility::SwitchToCameraOne(float timeBetweenCameraChanges, float smoothBlendTime)
{
	if (timeToNextCameraChange <= 0.0f)
	{
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController != nullptr)
		{
			AActor* newCameraTarget = nullptr;
			if (OurPlayerController->GetViewTarget() == CameraActor1)
			{
				newCameraTarget = CameraActor2;
			}
			else
			{
				newCameraTarget = CameraActor1;
			}
			OurPlayerController->SetViewTargetWithBlend(newCameraTarget, smoothBlendTime);
			timeToNextCameraChange += timeBetweenCameraChanges;
		}
	}
}

void ACameraUtility::SwitchToCameraTwo()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->SetViewTargetWithBlend(CameraActor2, 0.5f);
}
