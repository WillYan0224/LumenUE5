// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCompoentTest.generated.h"

UCLASS()
class LIGHTINGTEST_API AMyCompoentTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCompoentTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpotLightComponent* SpotLightComponent;

	UPROPERTY(EditAnywhere, Category = "Transformation")
	float Speed = 125.0f;
	UPROPERTY(EditAnywhere, Category = "Transformation")
	float MoveDistance = 600.0f;

	FVector StartLocation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
