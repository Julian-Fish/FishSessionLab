// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// define log category
DEFINE_LOG_CATEGORY_STATIC(LogFish, Log, All);

// new log marco
#define UE_LOG_FISH(str, ...) UE_LOG(LogFish, Log, TEXT(str), __VA_ARGS__);
