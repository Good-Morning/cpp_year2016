//
// Created by eugene on 11.10.2017
//
#pragma once

#include <CodeStyle.h>
#include <future.h>
#include <promise.h>

template<typename T>
Future<T> FLATTEN(Future<T> const &);

template<typename T>
Future<T> FLATTEN(Future<Future<T>> const &);

template<template<typename, typename...> class C, typename T>
Future<C<T>> FLATTEN(C<Future<T>> const &);
