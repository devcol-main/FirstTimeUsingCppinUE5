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
	
	FString CountNumPlayed = "Num Played: ";
	
	int32 numEventSuccess = 0;
	float TotalDistanceMoved = 0.f;
	
	for (int32 i = 0; i < 10; ++i)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, CountNumPlayed + FString::FromInt(i+1));
		}
		
		TriggerEvent(numEventSuccess, TotalDistanceMoved);
	
		
		//Move();
		//Turn();
	}
	
	// 1000.f = Time to display in seconds (effectively "endless" for a session)
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Emerald, FString("=== Summary ===") );
		
		GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Emerald, 
		FString("Total Moved Distance: ") + FString::SanitizeFloat(TotalDistanceMoved) + FString(" | ")  
					+ FString("Event Success: ") + FString::FromInt(numEventSuccess)
			);
		
		GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Emerald, FString("=== END ==="));
		
		
	}
	UE_LOG(LogTemp, Error, TEXT("numEventSuccess = %s"), * FString::FromInt(numEventSuccess) );
	UE_LOG(LogTemp, Error, TEXT("TotalDistanceMoved = %s"), * FString::SanitizeFloat(TotalDistanceMoved));
	
	
}

// Called every frame

/*
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/


void AMyActor::Move(float &TotalDistanceMoved)
{
	
	FVector BeforeMoveLocation = GetActorLocation();
	
	UE_LOG(LogTemp, Warning, TEXT("Move()"));

	FVector Target;

	// -50~50 까지 Random
	Target.X = FMath::FRandRange(-50.0, 50.0);
	Target.Y = FMath::FRandRange(-50.0, 50.0);
	Target.Z = 0;

	AddActorWorldOffset(Target);

	FVector CurrentLocation = GetActorLocation();
	
	float DistanceMoved = FVector::Dist(BeforeMoveLocation, CurrentLocation);
	
	TotalDistanceMoved += DistanceMoved;
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString("Move: ") + CurrentLocation.ToString() 
		+ FString(" | Distance Moved: ") +  FString::SanitizeFloat(DistanceMoved));	
		
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
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString("Rotation: ") +CurrentRotation.ToString());
	}
	UE_LOG(LogTemp, Warning, TEXT("Rotation = %s"), *CurrentRotation.ToString());
}

void AMyActor::TriggerEvent(int32 &NumS, float &TotalDistanceMoved)
{
	int32 randResult = FMath::RandRange(0, 1);
	bool isRandSucess;
	
	if (randResult)
	{
		isRandSucess = true;	
	}
	else
	{
		isRandSucess = false;
	}
	
	
	//UE_LOG(LogTemp, Warning, TEXT("TriggerEvent"));
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, TEXT("TriggerEvent Start"));
	}
	
	if (isRandSucess)
	{
		++NumS;
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Success"));
		
		Move(TotalDistanceMoved);
		Turn();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Failed"));
	}
	
	
	
}


