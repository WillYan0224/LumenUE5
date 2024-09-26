// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void Grab();
	
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void Release();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FRotator currentRotation;

private:
	UPROPERTY(EditAnywhere)
	float reach = 400.0f;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100.0f;

	UPROPERTY(EditAnywhere)
	float holdDistance = 200.0f;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
