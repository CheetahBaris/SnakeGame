// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 80.f;
	MovmentSpeed = 200.f;
	LastMoveDirection = EMovmentDirection::DOWM;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovmentSpeed);
	AddSnakeElement(5);
	
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move( );

}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{	
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform  );		 
		SnakeElements.Add(NewSnakeElem);

	}
}

void ASnakeBase::Move( )
{
	FVector MovmentVector(ForceInitToZero);
	float MovmentSpeed = ElementSize;
		 
	switch (LastMoveDirection)
	{

	case EMovmentDirection::UP:
		MovmentVector.X += MovmentSpeed;
		break;
	case EMovmentDirection::DOWM:
		MovmentVector.X -= MovmentSpeed;
		break;
	case EMovmentDirection::LEFT:
		MovmentVector.Y += MovmentSpeed;
		break;
	case EMovmentDirection::RIGHT:
		MovmentVector.Y -= MovmentSpeed;
		break;
	}


	 

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);

	}

	SnakeElements[0]->AddActorWorldOffset(MovmentVector); //AddActorWorldOffset(MovmentVector);
}

