// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true; // 
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{   
	//UE_LOG(LogTemp, Warning, TEXT("Before SUPER BeginPlay"));
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	
	// 0,0,5 에서 시작
	SetActorLocation(FVector(0, 0, 50));
	
	for (int32 i = 0; i < 10; ++i)
	{
		Move();
	}

	for (int32 i = 0; i < 10; ++i)
	{
		Turn();
	}
	
}

// Called every frame

/*
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/


void AMyActor::Move()
{
	UE_LOG(LogTemp, Warning, TEXT("Move()"));

	FVector Target;

	// -50~50 까지 Random
	Target.X = FMath::FRandRange(-50.0, 50.0);
	Target.Y = FMath::FRandRange(-50.0, 50.0);
	Target.Z = 0;

	AddActorWorldOffset(Target);

	FVector CurrentLocation = GetActorLocation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, CurrentLocation.ToString());
	}
	UE_LOG(LogTemp, Warning, TEXT("Location = %s"), * CurrentLocation.ToString());
}

void AMyActor::Turn()
{

	UE_LOG(LogTemp, Warning, TEXT("Turn()"));          

	FRotator DeltatRotation;
	DeltatRotation.Yaw = FMath::FRandRange(-180.0, 180.0);
	DeltatRotation.Pitch = 0;
	DeltatRotation.Roll = 0;
	
	AddActorWorldRotation(DeltatRotation);

	FRotator CurrentRotation = GetActorRotation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, CurrentRotation.ToString());
	}
	UE_LOG(LogTemp, Warning, TEXT("Rotation = %s"), *CurrentRotation.ToString());
}


